/*
 *  RayTracer.cpp
 *  Theme06_m01
 *
 *  Created by Carlos Olave on 12/11/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

//int count_hit = 0;

#include "RayTracer.h"

RayTracer::RayTracer(SceneReader &_scene) : JITTER_SIZE(16){
	scene = _scene;
	srand((unsigned)time(0));
}

RayTracer::~RayTracer() {
	scene.vSphereCollection.clear();
	scene.vTriangleCollection.clear();
	scene.vMaterialCollection.clear();
	scene.vPlaneCollection.clear();
	scene.vCameraCollection.clear();
	scene.vPointLightCollection.clear();
	scene.vDirectionalLightCollection.clear();
	scene.vAmbientLightCollection.clear();
	bool result = bvh->clean();
	if (!result) std::cout << "Failed to clean up BVH structure pointers." << std::endl;
	delete bvh;
	bvh = NULL;
	
}

iPoint RayTracer::FindIntersection(Ray &ray) {
	
	iPoint temp_sphere_point, sphere_point, result_point;
	sphere_point.isValid = false;
	temp_sphere_point.isValid = false;
	result_point.isValid = false;
	
	std::vector<iPoint> intersection_points;
	/*	
	// Find intersection among sphere objects if any.
	if (scene.vSphereCollection.size() != 0) {
	
		for (int i=0; i<scene.vSphereCollection.size(); i++) {
			temp_sphere_point = SphereIntersection(ray, scene.vSphereCollection[i]);
			
			// the returned point is a valid intersection.
			if (temp_sphere_point.isValid) {
				Material m = scene.vMaterialCollection[scene.vSphereCollection[i].getMaterialIndex()];
				temp_sphere_point.diffuse = m.getDiffuse();
				temp_sphere_point.specular = m.getSpecular();
				temp_sphere_point.ideal_specular = m.getIdealSpecular();
				temp_sphere_point.phong_exponent = m.getPhongExponent();
				sphere_point = temp_sphere_point;
				intersection_points.push_back(sphere_point);
			}
		}
	}
	*/
	
	iPoint temp_triangle_point, triangle_point;
	triangle_point.isValid = false;
	temp_triangle_point.isValid = false;
	
	
	bool isHit = bvh->hit(ray, 0.0f, 1.0f, 0.0f, temp_triangle_point);
	if (isHit && temp_triangle_point.isValid) {
		Material m = scene.vMaterialCollection[temp_triangle_point.material_index];
		temp_triangle_point.diffuse = m.getDiffuse();
		temp_triangle_point.specular = m.getSpecular();
		temp_triangle_point.ideal_specular = m.getIdealSpecular();
		temp_triangle_point.phong_exponent = m.getPhongExponent();
		triangle_point = temp_triangle_point;
		intersection_points.push_back(triangle_point);
	}
	
	/*
	if (scene.vTriangleCollection.size() != 0) {
	
		for (int i = 0; i<scene.vTriangleCollection.size(); i++) {
			temp_triangle_point = TriangleIntersection(ray, scene.vTriangleCollection[i]);
			
			// the retuned triangle point is valid intersection.
			if (temp_triangle_point.isValid) {
				//count_hit+=1;
				//cout << count_hit << std::endl;
				Material m = scene.vMaterialCollection[scene.vTriangleCollection[i].getMaterialIndex()];
				temp_triangle_point.diffuse = m.getDiffuse();
				temp_triangle_point.specular = m.getSpecular();
				temp_triangle_point.ideal_specular = m.getIdealSpecular();
				temp_triangle_point.phong_exponent = m.getPhongExponent();
				triangle_point = temp_triangle_point;
				intersection_points.push_back(triangle_point);
			}
		
		}
	}	
	*/
	
	iPoint temp_plane_point, plane_point;
	temp_plane_point.isValid = false;
	plane_point.isValid = false;
	
	if (scene.vPlaneCollection.size() != 0) {
	
		for (int i=0; i<(int)scene.vPlaneCollection.size(); i++) {
			temp_plane_point = PlaneIntersection(ray, scene.vPlaneCollection[i]);
		
			// the returned plane point is valid intersection.
			if (temp_plane_point.isValid) {
				
				Material m = scene.vMaterialCollection[scene.vPlaneCollection[i].getMaterialIndex()];
				temp_plane_point.diffuse = m.getDiffuse();
				temp_plane_point.specular = m.getSpecular();
				temp_plane_point.ideal_specular = m.getIdealSpecular();
				temp_plane_point.phong_exponent = m.getPhongExponent();
				plane_point = temp_plane_point;
				intersection_points.push_back(plane_point);
			}
			
		}
	}
	
	if (!intersection_points.empty()) result_point = intersection_points[0];
	
	iPoint temp_result_point;
	for (int i=0; i<(int)intersection_points.size(); i++) {
		temp_result_point = intersection_points[i];
		if (temp_result_point.t < result_point.t)
			result_point = temp_result_point;
	}
	
	return result_point;
}

iPoint RayTracer::SphereIntersection(Ray &ray, Sphere sphere) {
	
	// Set the default returned value a null point.
	iPoint intersection_point;
	intersection_point.isValid = false;
	
	float3 d = ray.d();
	float3 e = ray.e();
	float3 c = sphere.c();
	float r = sphere.r();
	
	float descriminant = (pow(DotProduct(d, Subtraction(e, c)), 2) - 
						  (DotProduct(d, d) * 
						  (DotProduct(Subtraction(e, c), Subtraction(e, c)) - 
						   pow(r, 2))));
	
	// ray and sphere do not intersect.
	if (descriminant < 0.0f) return intersection_point;
	
	// ray and sphere intersect
	float denominator = DotProduct(d, d);
	float nominator = -(DotProduct(d, Subtraction(e, c)));
	
	// Error checking.
	if (denominator == 0) return intersection_point;
	
	// calculate value of t.
	float t0 = (nominator + sqrt(descriminant))/denominator;
	float t1 = (nominator - sqrt(descriminant))/denominator;
	
	// take the smallest calculated t.
	float t = std::min(t0, t1);
	
	if (t < 0.0) return intersection_point;
	
	float3 point_p;
	point_p = e + t*d;
	
	float3 normal_p;
	normal_p = (point_p - c)/r;
	
	// Set the data for the intersection point.
	intersection_point.p = point_p;
	intersection_point.np = normal_p;
	intersection_point.t = t;
	intersection_point.isValid = true;
	
	return intersection_point;
}

iPoint RayTracer::TriangleIntersection(Ray &ray, Triangle triangle) {
	
	iPoint iPoint_triangle;
    iPoint_triangle.isValid = false;
	
	float3 direction = ray.d();
	float3 origin = ray.e();
	float3 v0 = triangle.a();
	float3 v1 = triangle.b();
	float3 v2 = triangle.c();
	double t, u, v;
	
	float3 edge10 = Subtraction(v1, v0);
	float3 edge20 = Subtraction(v2, v0);
	
	float3 pvec = CrossProduct(direction, edge20);
	float det = DotProduct(edge10, pvec);
	
	if (det < 0.0001) return iPoint_triangle;
	
	// Calculate distance from v0 to ray origin.
	float3 tvec = Subtraction(origin, v0);
	
	// Calculate U and test the bound for exclusion.
	u = DotProduct(tvec, pvec);
	if (u < 0.0 || u > det) return iPoint_triangle;
	
	// Prepare to calculate V.
	float3 qvec = CrossProduct(tvec, edge10);
	v = DotProduct(direction, qvec);
	if (v < 0.0 || (u+v) > det) return iPoint_triangle;
	
	// Ready to calculate t.
	t = DotProduct(edge20, qvec);
	
	if (t < 0.0) return iPoint_triangle;
	
	float inv_det = 1.0f/det;
	t *= inv_det;
	u *= inv_det;
	v *= inv_det;
	
	iPoint_triangle.p = origin + t*direction;
	
	float3 point_normal = CrossProduct(edge10, edge20);
	
	bool isObj = triangle.isTriangleObj();
	
	if (isObj) {
		float3 nv0 = triangle.na();
		float3 nv1 = triangle.nb();
		float3 nv2 = triangle.nc();
		point_normal = nv0 + u*(nv1-nv0) + v*(nv2-nv0);
	}
	
	iPoint_triangle.np = Normalize(point_normal);
	iPoint_triangle.isValid = true;
	iPoint_triangle.t = t;
	return iPoint_triangle;
}

iPoint RayTracer::PlaneIntersection(Ray &ray, Plane plane) {
	iPoint iPoint_plane;
	iPoint_plane.isValid = false;
	
	//return iPoint_plane;
	
	float d = plane.getPlaneScalar();
	float3 n = plane.getPlaneNormal();
	
	float3 direction = Normalize(ray.d());
	float3 origin = ray.e();
	
	float t0 = DotProduct(direction, n);
	
	// Plane is parallalel -> no intersection.
	if (t0 == 0) return iPoint_plane;
	
	// The ray is pointing away. We need to revese the plane normal.
	if (t0 < 0) n = 1*n;
	
	float t1 = -(DotProduct(n, origin) + d);
	
	float t = t1/t0;
	
	// if(t<0) then ray intersects plane behind origin O
	if (t > 0.0) {
		float3 point = origin + t*direction;
		float3 point_normal = n;
	
		iPoint_plane.p = point;
		iPoint_plane.np = point_normal;
		iPoint_plane.isValid = true;
		iPoint_plane.t = t;
	}
	
	return iPoint_plane;
}

float RayTracer::RandomFloat(float a, float b) {
	return ((b-a)*((float)rand()/RAND_MAX))+a;
}

BVH* RayTracer::GenerateBVH() {

	int t_size = 0;
	
	if (!scene.vTriangleCollection.empty())
		t_size = scene.vTriangleCollection.size();
	
	if (!scene.vSphereCollection.empty())
		t_size += scene.vSphereCollection.size();
	
	Surface** surfaces;
	
	surfaces = new Surface*[t_size];
	
	int index = 0;
	
	Sphere sp;
	if (!scene.vSphereCollection.empty()) {
		for (int i=0; i<(int)scene.vSphereCollection.size(); i++) {
			sp = scene.vSphereCollection[i];
			surfaces[index] = new Sphere(sp.c(), sp.r());
	
			surfaces[index]->setMaterialIndex(sp.getMaterialIndex());
			index+=1;
		}
	}
	
	Triangle tri;
	if (!scene.vTriangleCollection.empty()) {
		for (int i=0; i<(int)scene.vTriangleCollection.size(); i++) {
			tri = scene.vTriangleCollection[i];
			if (tri.isTriangleObj())
				surfaces[index] = new Triangle(tri.a(), tri.b(), tri.c(),
									   tri.na(), tri.b(), tri.c());
			else
				surfaces[index] = new Triangle(tri.a(), tri.b(), tri.c());
	
			surfaces[index]->setMaterialIndex(tri.getMaterialIndex());
			
			index+=1;
		}
	}
	
	return new BVH(surfaces, index);
}

void RayTracer::GenerateJitterSample() {
	
	for (int i=0; i<JITTER_SIZE; i++) {
		
		// Clear out the jitter array data.
		jitter[i][0] = 0.0f;
		jitter[i][1] = 0.0;
		
		// Generate random jitter.
		jitter[i][0] = RandomFloat(-0.5f, 0.5f);
		jitter[i][1] = RandomFloat(-0.5f, 0.5f);
	}
}

void RayTracer::SetCamera(Camera &camera) {
	
	float3 view_direction = camera.getCameraViewDirection();
	float3 w = -1*Normalize(view_direction);
	
	float3 up_vector;
	up_vector.x = 0.0f;
	up_vector.y = 1.0f;
	up_vector.z = 0.0f;
	
	float3 u = CrossProduct(w, up_vector);
	float3 v = CrossProduct(w, u);
	
	camera.setW(w);
	camera.setU(Normalize(u));
	camera.setV(Normalize(v));
	camera.setVectorViewDirection(Normalize(view_direction));
	
	float right = -camera.getImageWidth()/2.0f;
	float left = camera.getImageWidth()/2.0f;
	
	float bottom = -camera.getImageHeight()/2.0f;
	float top = camera.getImageHeight()/2.0f;
	
	camera.setLeft(left);
	camera.setRight(right);
	camera.setTop(top);
	camera.setBottom(bottom);
}

void RayTracer::WriteRgba(const char fileName[], const Rgba *pixels, int w, int h) {
	RgbaOutputFile file(fileName, w, h, WRITE_RGBA);
	file.setFrameBuffer(pixels, 1, w);
	file.writePixels(h);
}

void RayTracer::CalculatePixelColor(float3 &color, const iPoint ip, Ray ray) {
	
	float3 ambient_term;
	
	for (int i=0; i<(int)scene.vAmbientLightCollection.size(); i++) {
		ambient_term = ip.diffuse*scene.vAmbientLightCollection[i].AmbientColor();
		color.x += ip.diffuse.x*ambient_term.x;
		color.y += ip.diffuse.y*ambient_term.y;
		color.z += ip.diffuse.z*ambient_term.z;
	}
	
	float3 P = ip.p;
	float3 N = Normalize(ip.np);
	float3 L;
	float3 V;
	float3 H;
	float3 diffuse_term;
	float3 specular_term;
	float3 total_contribution;
	float3 drl_direction;
	float3 drl_color;
	float diffuse_light;
	float specular_light;
	
	// Calculate blinn phong for directional light.
	for (int i=0; i<(int)scene.vDirectionalLightCollection.size(); i++) {
		
		// Determine if the object is obscure by another object.
		bool directional_shadow_blocked = ShadowRayTracing(P, scene.vDirectionalLightCollection[i]);
		if (directional_shadow_blocked) continue;
		
		// Get the directional light direction and color.
		drl_direction = scene.vDirectionalLightCollection[i].LightDirection();
		drl_color = scene.vDirectionalLightCollection[i].LightColor();
		
		// Compute diffuse contribution.
		L = Normalize(-1*drl_direction);
		diffuse_light = std::max((float)DotProduct(L, N), 0.0f);
		diffuse_term = ip.diffuse*drl_color*diffuse_light;
		
		// Compute Specular contribution.
		V = Normalize(Subtraction(ray.e(), P));
		H = Normalize(Addition(L, V));
		specular_light = powf(std::max((float)DotProduct(H, N), 0.0f), ip.phong_exponent);
		if (diffuse_light <= 0) specular_light = 0.0f;
		specular_term = ip.specular*drl_color*specular_light;
		
		total_contribution = Addition(diffuse_term, specular_term);
		
		color.x += ip.diffuse.x*total_contribution.x;
		color.y += ip.diffuse.y*total_contribution.y;
		color.z += ip.diffuse.z*total_contribution.z;
	}
	
	// Calculate blinn phong for point light.
	for (int i=0; i<(int)scene.vPointLightCollection.size(); i++) {
		
		// Determine if the object is obscure by another object.
		bool shadow_blocked = ShadowRayTracing(P, scene.vPointLightCollection[i].LightPosition());
		if (shadow_blocked) continue;
		
		// Compute Diffuse contribution.
		L = Normalize(Subtraction(scene.vPointLightCollection[i].LightPosition(), P));
		diffuse_light = std::max((float)DotProduct(L, N), 0.0f);
		diffuse_term = ip.diffuse*scene.vPointLightCollection[i].LightColor()*diffuse_light;
		
		// Compute Specular contribution.
		V = Normalize(Subtraction(ray.e(), P));;
		H = Normalize(Addition(L, V));
		specular_light = powf(std::max((float)DotProduct(H, N), 0.0f), ip.phong_exponent);
		if (diffuse_light <= 0) specular_light = 0.0f;
	
		specular_term = ip.specular*scene.vPointLightCollection[i].LightColor()*specular_light;
			
		total_contribution = Addition(diffuse_term, specular_term);
		
		color.x += ip.diffuse.x*total_contribution.x;
		color.y += ip.diffuse.y*total_contribution.y;
		color.z += ip.diffuse.z*total_contribution.z;
	}
}

float3 RayTracer::RayTracing(Ray ray, float3 color, iPoint ip, int current_depth, int max_depth) {
	
	if (current_depth > max_depth) {
		return color;
	}
	
	// Find an intersection with objects
	ip = FindIntersection(ray);
	if (!ip.isValid) {
		
		// If no intersection is found
		// then set the pixel color to background.
		color.x = 0.000f;
		color.y = 0.000f;
		color.z = 0.000f;
	}
	else {
		// Calculate blinn Phong Lighting.
		CalculatePixelColor(color, ip, ray);
		
		
		// Calculate the reflection contribution.
		if (ip.ideal_specular.x > 0.0f ||
			ip.ideal_specular.y > 0.0f ||
			ip.ideal_specular.z > 0.0f) {
			
			float3 N = ip.np;
			float3 D = Normalize(ray.d());
			float3 R = D - 2.0f * DotProduct(D, N) * N;
			
			if (current_depth < max_depth) {
			
				float3 reflection_color;
				reflection_color.x = 0.0f;
				reflection_color.y = 0.0f;
				reflection_color.z = 0.0f;
				
				// Set the new ray properties
				Ray reflection_ray;
				reflection_ray.SetOrigin(ip.p + R*(.0001));
				reflection_ray.SetDirection(R);
				
				reflection_color = RayTracing(reflection_ray, reflection_color, ip, current_depth+1, max_depth);
			
				color = color + ip.ideal_specular * reflection_color;
				
			}
		}
		
	}	
	
	return color;
}

bool RayTracer::ShadowRayTracing(float3 point_position, float3 light_position) {
	
	// Storage for intersection validation.
	iPoint shadow_intersection_point;
	shadow_intersection_point.isValid = false;
	
	// Create a new ray where origin is the current intersected point,
	// and the direction is from origin to light position.
	Ray ray;
	float3 L = light_position - point_position;
	ray.SetOrigin(point_position + L*(.0001));
	ray.SetDirection(L);
	
	// Cast the ray to see if we find a intersection with
	// an object before reaching the light.
	shadow_intersection_point = FindIntersection(ray);
	
	if (shadow_intersection_point.t < 0.00001 ||
		shadow_intersection_point.t > 10000.0) return false;
	
	// isValid indicates if intersection was reached/hit
	if (shadow_intersection_point.isValid) return true;
		
	return false;
}

bool RayTracer::ShadowRayTracing(float3 point_position, DirectionalLight drl) {

	// Storage for intersection validation.
	iPoint shadow_intersection_point;
	shadow_intersection_point.isValid = false;
	
	// Create a new ray where origin is the current intersected point
	// and the direction is from origin to light position.
	Ray ray;
	float3 L = -1*drl.LightDirection();
	ray.SetOrigin(point_position + L*(.0001));
	ray.SetDirection(L);
	
	// Cast the ray to see if we find a intersection with
	// an object before reacing the light.
	shadow_intersection_point = FindIntersection(ray);
	
	if (shadow_intersection_point.t < 0.00001 ||
		shadow_intersection_point.t > 10000.0) return false;
	
	// isValid indicates if intersection was reached/hit.
	if (shadow_intersection_point.isValid) return true;
	
	return false;
}

bool RayTracer::DrawScene() {
	
	// Ensure camera collection contains at least one camera.
	// Ensure support for a single camera.
	if (scene.vCameraCollection.empty() ||
		scene.vCameraCollection.size() > 1) return false;
	
	bvh = GenerateBVH();
	
	// Get the camera properties
	Camera camera = scene.vCameraCollection[0];
	SetCamera(camera);
	
	// Camera Properties.
	float3 U = camera.getU();
	float3 V = camera.getV();
	float3 neg_W = camera.getVectorViewDirection();
	float3 e = camera.getOrigin();
	
	float d = camera.getFocalLeght();
	float l = camera.getLeft();
	float r = camera.getRight();
	float t = camera.getTop();
	float b = camera.getBottom();
	int nx = camera.getImagePixelsWidth();
	int ny = camera.getImagePixelsHeight();
	
	// The container to hold the traced image.
	Array2D<Rgba> pixels;
	pixels.resizeErase(ny, nx);
	
	float du = 0.0f;
	float dv = 0.0f;

	// intersection point.
	iPoint ip;
	ip.isValid = false;
	
	// a single ray.
	Ray ray;
	
	// the color per pixel.
	float3 color;
	
	// Jitter coordinates.
	float jitter_i;
	float jitter_j;
	
	// Generate the jitter samples.
	GenerateJitterSample();
	
	// ray trace.
	for (int i=0; i<nx; i++) {
		for (int j=0; j<ny; j++) {
			
			// default pixel color.
			Rgba &pixel = pixels[j][i];
			pixel.r = 0.0f;
			pixel.g = 0.0f;
			pixel.b = 0.0f;
			pixel.a = 0.0f;
			
			for (int jitter_index=0; jitter_index<JITTER_SIZE; jitter_index++) {
				
				// jitter x and x coordinates.
				jitter_i = i + jitter[jitter_index][0];
				jitter_j = j + jitter[jitter_index][1];
			
				// Coordinates of the pixel's position on the image plane,
				// measured with respect to the origin e and the basis {u, v}.
				du = l + (r - l)*(jitter_i + 0.5f)/nx;
				dv = b + (t - b)*(jitter_j + 0.5f)/ny;
			
				// Set camera properties.
				ray.SetOrigin(e);
				ray.SetDirection(d*neg_W + du*U + dv*V);
			
				// default color.
				color.x = 0.0f;
				color.y = 0.0f;
				color.z = 0.0f;

				// Recursive call.
				color = RayTracing(ray, color, ip, 0, 1);
							
				pixel.r += color.x;
				pixel.g += color.y;
				pixel.b += color.z;
			}
			
			pixel.r /= JITTER_SIZE;
			pixel.g /= JITTER_SIZE;
			pixel.b /= JITTER_SIZE;
			pixel.a = 1.0f;
		}
	}
	
	// print final image.
	const char name[] = "test.exr";
	WriteRgba(name, &pixels[0][0], nx, ny);
	
	// Exit success.
	return true;
}