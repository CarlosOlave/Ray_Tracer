/*
 *  Objects.h
 *  Theme06_m01
 *
 *  Created by Carlos Olave on 12/9/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

#ifndef OBJECTS_H
#define OBJECTS_H

#include "parse.h"
#include "Vectors.h"
#include "bvh_box.h"
#include "Surface.h"

class Material {
		
	private:
		float3 diffuse;
		float3 specular;
		float3 ideal_specular;
		float phong_exponent;
		
	public:
		Material();
		Material(float3 _diffuse, float3 _specular, 
				 float _phong_exponent, float3 _ideal_specular);
		float3 getDiffuse() {return diffuse;}
		float3 getSpecular() {return specular;}
		float3 getIdealSpecular() {return ideal_specular;}
		float getPhongExponent() {return phong_exponent;}
};
	
class Sphere : public Surface {
	
private:
	float3 position;
	float radius;
	int material_index;
	
public:
	Sphere();
	Sphere(float3 _position, float _radius);
	float3 c() {return position;}
	float r() {return radius;}
	int getMaterialIndex() {return material_index;}
	void setMaterialIndex(int i) {material_index = i;}
	
	// Virtual
	bool hit(Ray &ray, float t_min, float t_max, float time, iPoint &hit_point);
	BVH_Box getBoundingBox();
};

class Triangle : public Surface {
	
private:
	float3 point1;
	float3 point2;
	float3 point3;
	int material_index;
	BVH_Box box;
	
	// obj properties.
	bool isObj;
	float3 point1_normal;
	float3 point2_normal;
	float3 point3_normal;
	
public:
	Triangle();
	Triangle(float3 _point1, float3 _point2, float3 _point3);
	Triangle(float3 _p1, float3 _p2, float3 _p3,
			 float3 _np1, float3 _np2, float3 _np3);	
	// setters
	void setMaterialIndex(int i) { material_index = i; }
	
	// Accessors.
	float3 a() { return point1; }
	float3 b() { return point2; }
	float3 c() { return point3; }
	float3 na() { return point1_normal;}
	float3 nb() { return point2_normal;}
	float3 nc() { return point3_normal;}
	bool isTriangleObj() {return isObj;}
	int getMaterialIndex() { return material_index; }
	
	// Virtual
	bool hit(Ray &ray, float t_min, float t_max, float time, iPoint &hit_point);
	BVH_Box getBoundingBox();
};

class Plane {

private:
	float3 normal;
	float scaler;
	int material_index;
	
public:
	Plane();
	Plane(float3 _normal, float _scalar);
	
	// Setters.
	void setMaterialIndex(int i) {material_index = i;}
	
	// Accessors.
	float getPlaneScalar() {return scaler;}
	float3 getPlaneNormal() {return normal;}
	int getMaterialIndex() {return material_index;}

};

class Camera {

private:
	float3 position;
	float3 direction;
	float3 u;
	float3 v;
	float3 w;
	float3 up;
	float3 view_direction;
	float focal_lenght;
	float left;
	float right;
	float bottom;
	float top;
	float image_width;
	float image_height;
	int image_pixels_width;
	int image_pixels_height;
	
public:
	Camera();
	Camera(float3 _position, float3 _direction, float _focal_length, 
		   float _image_width, float _image_height, int _image_pixels_width,
		   int _image_pixels_height);
	
	float3 getCameraViewDirection() {return direction;}
	float3 getVectorViewDirection() {return -1*w;}
	float3 getU() {return u;}
	float3 getV() {return v;}
	float3 getOrigin() {return position;}
	float getImageWidth() {return image_width;}
	float getImageHeight() {return image_height;}
	float getFocalLeght() {return focal_lenght;}
	float getLeft() {return left;}
	float getRight() {return right;}
	float getTop() {return top;}
	float getBottom() {return bottom;}
	float getImagePixelsWidth() {return image_pixels_width;}
	float getImagePixelsHeight() {return image_pixels_height;}
	
	void setU(float3 _u) {u = _u;}
	void setV(float3 _v) {v = _v;}
	void setW(float3 _w) {w = _w;}
	void setVectorViewDirection(float3 _view_direction) {view_direction = _view_direction;}
	void setLeft(float _left) {left = _left;}
	void setRight(float _right) {right = _right;}
	void setTop(float _top) {top = _top;}
	void setBottom(float _bottom) {bottom = _bottom;}
	
	// Accessors
	float3 e() {return position;};
	float3 _u() {return u;}
	float3 _v() {return v;}
	float3 neg_w();
	float l() {return left;}
	float r() {return right;}
	float t() {return top;}
	float b() {return bottom;}
	float iw() {return image_width;}
	float ih() {return image_height;}
	float d() {return focal_lenght;}
	int pw() {return image_pixels_width;}
	int ph() {return image_pixels_height;}
	
};

class PointLight {

private:
	float3 position;
	float3 rgb;
	
public:
	PointLight();
	PointLight(float3 _position, float3 _rgb);
	
	float3 LightPosition() {return position;}
	float3 LightColor() {return rgb;}
	
};

class DirectionalLight {

private:
	float3 direction;
	float3 rgb;
	
public:
	DirectionalLight();
	DirectionalLight(float3 _direction, float3 _rgb);
	
	float3 LightDirection() { return direction; }
	float3 LightColor() { return rgb; }
};

class AmbientLight {
	
private:
	float3 rgb;
	
public:
	AmbientLight();
	AmbientLight(float3 _rgb);
	
	float3 AmbientColor() {return rgb;}
	
};

#endif 