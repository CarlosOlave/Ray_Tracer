/*
 *  RayTracer.h
 *  Theme06_m01
 *
 *  Created by Carlos Olave on 12/11/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "SceneReader.h"
#include "Objects.h"
#include "Vectors.h"
#include "Ray.h"
#include "BVH.h"
#include <cstdlib>
#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>

using namespace Imf;
using namespace Imath;

class RayTracer : public Camera {
	
private:
	SceneReader scene;
	BVH *bvh;
	float jitter[16][2];
	const int JITTER_SIZE;
	
public:
	RayTracer(SceneReader &_scene);
	~RayTracer();
	bool DrawScene();
	bool ShadowRayTracing(float3 point_position, float3 light_position);
	bool ShadowRayTracing(float3 point_position, DirectionalLight drl);
	float RandomFloat(float a, float b);
	float3 RayTracing(Ray ray, float3 color, iPoint ip, int current_depth, int max_depth);
	void WriteRgba (const char fileName[], const Rgba *pixels, int width, int height);
	void CalculatePixelColor(float3 &color, const iPoint ip, Ray ray);
	void SetCamera(Camera &camera);
	void GenerateJitterSample();
	
	// Intersection Functions.
	iPoint FindIntersection(Ray &ray);	
	iPoint SphereIntersection(Ray &ray, Sphere sphere);
	iPoint TriangleIntersection(Ray &ray, Triangle triangle);
	iPoint PlaneIntersection(Ray &ray, Plane plane);
	
	// Genereate BVH 
	BVH* GenerateBVH();
};

#endif