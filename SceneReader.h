/*
 *  SceneReader.h
 *  Theme06_m01
 *
 *  Created by Carlos Olave on 12/8/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

#ifndef SCENEREADER_H
#define SCENEREADER_H

#include "parse.h"
#include "Objects.h"
#include <vector>

class SceneReader : public Parser {
	
	int current_material_index;
	
	virtual void sphere(float3 pos, float r);
	virtual void triangle(float3 p1, float3 p2, float3 p3);
	virtual void triangle(float3 p1, float3 p2, float3 p3, 
						  float3 np1, float3 np2, float3 np3);
	virtual void plane(float3 n, float d);
	virtual void camera(float3 pos, float3 dir, float d, float iw, float ih, int pw, int ph);
	virtual void pointLight(float3 pos, float3 rgb);
	virtual void directionalLight(float3 dir, float3 rgb);
	virtual void ambientLight(float3 rgb);
	virtual void material(float3 diff, float3 spec, float r, float3 refl);

public:
	SceneReader();
	~SceneReader();
	virtual void parse(const char* name);
	std::vector<Material> vMaterialCollection;	
	std::vector<Sphere> vSphereCollection;
	std::vector<Triangle> vTriangleCollection;
	std::vector<Plane> vPlaneCollection;
	std::vector<Camera> vCameraCollection;
	std::vector<PointLight> vPointLightCollection;
	std::vector<DirectionalLight> vDirectionalLightCollection;
	std::vector<AmbientLight> vAmbientLightCollection;
};

#endif