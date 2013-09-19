/*
 *  Objects.cpp
 *  Theme06_m01
 *
 *  Created by Carlos Olave on 12/9/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

#include "Objects.h"

/* MATERIAL */

Material::Material() {
}

Material::Material(float3 _diffuse, float3 _specular,
				   float _phong_exponent, float3 _ideal_specular) {
	diffuse = _diffuse;
	specular = _specular;
	ideal_specular = _ideal_specular;
	phong_exponent = _phong_exponent;
}

/* SPHERE */

Sphere::Sphere() {
}

Sphere::Sphere(float3 _position, float _radius) {
	position = _position;
	radius = _radius;
}

bool Sphere::hit(Ray &ray, float t_min, float t_max, float time, iPoint &hit_point) {
	
	float3 d = ray.d();
	float3 e = ray.e();
	float3 c = position;
	float r = radius;
	
	float descriminant = (pow(DotProduct(d, Subtraction(e, c)), 2) - 
						  (DotProduct(d, d) * 
						   (DotProduct(Subtraction(e, c), Subtraction(e, c)) - 
							pow(r, 2))));
	
	// ray and sphere do not intersect.
	if (descriminant < 0.0f) return false;
	
	// ray and sphere intersect
	float denominator = DotProduct(d, d);
	float nominator = -(DotProduct(d, Subtraction(e, c)));
	
	// Error checking.
	if (denominator == 0) return false;
	
	// calculate value of t.
	float t0 = (nominator + sqrt(descriminant))/denominator;
	float t1 = (nominator - sqrt(descriminant))/denominator;
	
	// take the smallest calculated t.
	float t = std::min(t0, t1);
	
	if (t < 0.0) return false;
	
	float3 point_p;
	point_p = e + t*d;
	
	float3 normal_p;
	normal_p = (point_p - c)/r;
	
	// Set the data for the intersection point.
	hit_point.p = point_p;
	hit_point.np = Normalize(normal_p);
	hit_point.t = t;
	hit_point.isValid = true;
	hit_point.material_index = material_index;
	
	return true;
}

BVH_Box Sphere::getBoundingBox() {
	
	float3 temp;
	temp.x = radius;
	temp.y = radius;
	temp.z = radius;
	return BVH_Box((position - temp), (position + temp)); 
}

/* TRIANGLE */

Triangle::Triangle(){
}

Triangle::Triangle(float3 _point1, float3 _point2, float3 _point3) {
	point1 = _point1;
	point2 = _point2;
	point3 = _point3;
	isObj = false;
}

Triangle::Triangle(float3 _p1, float3 _p2, float3 _p3,
				   float3 _np1, float3 _np2, float3 _np3) {

	point1 = _p1;
	point2 = _p2;
	point3 = _p3;
	point1_normal = _np1;
	point2_normal = _np2;
	point3_normal = _np3;
	isObj = true;
}

bool Triangle::hit(Ray &ray, float t_min, float t_max, float time, iPoint &hit_point) {

	//hit_point.isValid = false;
	
	float3 direction = ray.d();
	float3 origin = ray.e();
	float3 v0 = point1;
	float3 v1 = point2;
	float3 v2 = point3;
	float t, u, v;
	
	float3 edge10 = Subtraction(v1, v0);
	float3 edge20 = Subtraction(v2, v0);
	
	float3 pvec = CrossProduct(direction, edge20);
	float det = DotProduct(edge10, pvec);
	
	if (det < 0.0001) return false;
	
	// Calculate distance from v0 to ray origin.
	float3 tvec = Subtraction(origin, v0);
	
	// Calculate U and test the bound for exclusion.
	u = DotProduct(tvec, pvec);
	if (u < 0.0 || u > det) return false;
	
	// Prepare to calculate V.
	float3 qvec = CrossProduct(tvec, edge10);
	v = DotProduct(direction, qvec);
	if (v < 0.0 || (u+v) > det) return false;
	
	// Ready to calculate t.
	t = DotProduct(edge20, qvec);
	
	if (t < 0.0) return false;
	
	float inv_det = 1.0f/det;
	t *= inv_det;
	u *= inv_det;
	v *= inv_det;
	
	hit_point.p = origin + t*direction;

	float3 point_normal = CrossProduct(edge10, edge20);
	
	if (isObj) {
		float3 nv0 = point1_normal;
		float3 nv1 = point2_normal;
		float3 nv2 = point3_normal;
		point_normal = nv0 + u*(nv1-nv0) + v*(nv2-nv0);
	}
	
	hit_point.np = Normalize(point_normal);
	hit_point.isValid = true;
	hit_point.t = t;
	hit_point.material_index = material_index;
	
	return true;
}

BVH_Box Triangle::getBoundingBox() {
	
	const float epsilon = 0.00001f;
	float3 min_point;
	float3 max_point;
	
	min_point.x = (point1.x < point2.x? point1.x : point2.x);
	min_point.y = (point1.y < point2.y? point1.y : point2.y);
	min_point.z = (point1.z < point2.z? point1.z : point2.z);
	
	min_point.x = (point3.x < min_point.x? point3.x : min_point.x);
	min_point.y = (point3.y < min_point.y? point3.y : min_point.y);
	min_point.z = (point3.z < min_point.z? point3.z : min_point.z);
	
	max_point.x = (point1.x > point2.x ? point1.x : point2.x);
	max_point.y = (point1.y > point2.y ? point1.y : point2.y);
	max_point.z = (point1.z > point2.z ? point1.z : point2.z);
	
	max_point.x = (point3.x > max_point.x ? point3.x : max_point.x);
	max_point.y = (point3.y > max_point.y ? point3.y : max_point.y);
	max_point.z = (point3.z > max_point.z ? point3.z : max_point.z);
	
	min_point.x = min_point.x - epsilon;
	min_point.y = min_point.y - epsilon;
	min_point.z = min_point.z - epsilon;
	
	max_point.x = max_point.x + epsilon;
	max_point.y = max_point.y + epsilon;
	max_point.z = max_point.z + epsilon;
	
	return BVH_Box(min_point, max_point);
}

/* PLANE */

Plane::Plane() {
}

Plane::Plane(float3 _normal, float _scalar) {
	normal = _normal;
	scaler = _scalar;
}

/* POINT LIGHT */

PointLight::PointLight() {
}

PointLight::PointLight(float3 _position, float3 _rgb) {
	position = _position;
	rgb = _rgb;
}

/* CAMERA */

Camera::Camera() {
}

Camera::Camera(float3 _position, float3 _direction, float _focal_length,
			   float _image_width, float _image_height, int _image_pixels_width,
			   int _image_pixels_height) {
	position = _position;
	direction = _direction;
	focal_lenght = _focal_length;
	image_width = _image_width;
	image_height = _image_height;
	image_pixels_width = _image_pixels_width;
	image_pixels_height = _image_pixels_height;
}

float3 Camera::neg_w() {
	float3 _w = w;
	_w.x = -(_w.x);
	_w.y = -(_w.y);
	_w.z = -(_w.z);
	return _w;
}

/* DIRECTIONAL LIGHT */

DirectionalLight::DirectionalLight() {
}

DirectionalLight::DirectionalLight(float3 _direction, float3 _rgb) {
	direction = _direction;
	rgb = _rgb;
}

/* AMBIENT LIGHT */

AmbientLight::AmbientLight() {
}

AmbientLight::AmbientLight(float3 _rgb) {
	rgb = _rgb;
}
