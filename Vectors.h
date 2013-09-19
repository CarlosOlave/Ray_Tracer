/*
 *  Vectors.h
 *  Theme06_m01
 *
 *  Created by Carlos Olave on 12/11/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

#ifndef VECTORS_H
#define VECTORS_H

#include "parse.h"
#include <cmath>


inline float3 Normalize(const float3 v) {
	double l = sqrt((v.x*v.x) + (v.y*v.y) + (v.z*v.z));
	float3 nv;
	nv.x = v.x/l;
	nv.y = v.y/l;
	nv.z = v.z/l;
	return nv;
}

inline float3 ScalarMult(const float3 v, const float k) {
	float3 vk;
	vk.x = v.x * k;
	vk.y = v.y * k;
	vk.z = v.z * k;
	return vk;
}

inline float3 CrossProduct(const float3 a, const float3 b) {
	float3 ab;
	ab.x = (a.y*b.z) - (a.z*b.y);
	ab.y = (a.z*b.x) - (a.x*b.z);
	ab.z = (a.x*b.y) - (a.y*b.x);
	return ab;
}

inline float3 Addition(const float3 a, const float3 b) {
	float3 c;
	c.x = (a.x + b.x);
	c.y = (a.y + b.y);
	c.z = (a.z + b.z);	
	return c;
}

inline float3 Subtraction(const float3 a, const float3 b) {
	float3 c;
	c.x = (a.x - b.x);
	c.y = (a.y - b.y);
	c.z = (a.z - b.z);
	return c;
}

inline float3 operator*(const float3 &a, float b) {
	float3 r;
	r.x = a.x * b;
	r.y = a.y * b;
	r.z = a.z * b;
	return r;
}

inline float3 operator*(float b, const float3 &a) {
	float3 r;
	r.x = a.x * b;
	r.y = a.y * b;
	r.z = a.z * b;
	return r;
}

inline float3 operator*(const float3 &a, const float3 &b) {
	float3 c;
	c.x = a.x * b.x;
	c.y = a.y * b.y;
	c.z = a.z * b.z;
	return c;
}

inline float3 operator/(const float3 &a, float b) {
	float3 r;
	r.x = a.x / b;
	r.y = a.y / b;
	r.z = a.z / b;
	return r;
}

inline float3 operator/(float b, const float3 &a) {
	float3 r;
	r.x = a.x / b;
	r.y = a.y / b;
	r.z = a.z / b;
	return r;
}

inline float3 operator-(const float3 &a, const float3 &b) {
	float3 c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return c;
}

inline float3 operator+(const float3 &a, const float3 &b) {
	float3 c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return c;
}

inline float Length(const float3 &a) {
	return sqrtf(a.x*a.x + a.y*a.y + a.z*a.z);
}

inline double DotProduct(const float3 a, const float3 b) {
	return ((a.x*b.x) + (a.y*b.y) + (a.z*b.z));
}

#endif