/*
 *  SceneReader.cpp
 *  Theme06_m01
 *
 *  Created by Carlos Olave on 12/8/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

#include "SceneReader.h"

SceneReader::SceneReader() {
	current_material_index = 0;
	vSphereCollection = std::vector<Sphere>();
	vTriangleCollection = std::vector<Triangle>();
	vPlaneCollection = std::vector<Plane>();
	vCameraCollection = std::vector<Camera>();
	vPointLightCollection = std::vector<PointLight>();
	vDirectionalLightCollection = std::vector<DirectionalLight>();
	vAmbientLightCollection = std::vector<AmbientLight>();
	vMaterialCollection = std::vector<Material>();
}

SceneReader::~SceneReader() {
	vSphereCollection.clear();
	vTriangleCollection.clear();
	vPlaneCollection.clear();
	vCameraCollection.clear();
	vPointLightCollection.clear();
	vDirectionalLightCollection.clear();
	vAmbientLightCollection.clear();
	vMaterialCollection.clear();
}

void SceneReader::sphere(float3 pos, float r) {
	Sphere sphere = Sphere(pos, r);
	
	// save the index of the material for this sphere.
	if (!vMaterialCollection.empty()) {
		sphere.setMaterialIndex(vMaterialCollection.size() - 1);
	}
	
	vSphereCollection.push_back(sphere);
}

void SceneReader::triangle(float3 p1, float3 p2, float3 p3) {
	Triangle triangle = Triangle(p1, p2, p3);
	
	// save the index of the material for this triangle.
	if (!vMaterialCollection.empty()) {	
		triangle.setMaterialIndex(vMaterialCollection.size() - 1);
	}
	
	vTriangleCollection.push_back(triangle);
}

void SceneReader::triangle(float3 p1, float3 p2, float3 p3,
						   float3 np1, float3 np2, float3 np3) {
	
	Triangle triangle = Triangle(p1, p2, p3, np1, np2, np3);
	
	// save the index of the material for this triangle.
	if (!vMaterialCollection.empty()) {
		triangle.setMaterialIndex(vMaterialCollection.size() - 1);
	}
	
	vTriangleCollection.push_back(triangle);
	
}

void SceneReader::plane(float3 n, float d) {
	Plane plane = Plane(n, d);
	
	// save the index of the material for this plane.
	if (!vMaterialCollection.empty()) {
		plane.setMaterialIndex(vMaterialCollection.size() - 1);
	}
	
	vPlaneCollection.push_back(plane);
}

void SceneReader::camera(float3 pos, float3 dir, float d, float iw, float ih, int pw, int ph) {
	Camera camera = Camera(pos, dir, d, iw, ih, pw, ph);
	vCameraCollection.push_back(camera);
}

void SceneReader::pointLight(float3 pos, float3 rgb) {
	PointLight pointLight = PointLight(pos, rgb);
	vPointLightCollection.push_back(pointLight);
}

void SceneReader::directionalLight(float3 dir, float3 rgb) {
	DirectionalLight directLight = DirectionalLight(dir, rgb);
	vDirectionalLightCollection.push_back(directLight);
}

void SceneReader::ambientLight(float3 rgb) {
	AmbientLight ambientLight = AmbientLight(rgb);
	vAmbientLightCollection.push_back(ambientLight);
}

void SceneReader::material(float3 diff, float3 spec, float r, float3 refl) {
	Material material = Material(diff, spec, r, refl);
	vMaterialCollection.push_back(material);
}

void SceneReader::parse(const char* name) {
	Parser::parse(name);
}


