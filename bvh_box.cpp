/*
 *  bvh_box.cpp
 *  Theme06_m01
 *
 *  Created by Carlos Olave on 12/18/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

#include "bvh_box.h"

BVH_Box::BVH_Box() {}

BVH_Box::BVH_Box(float3 _min_point, float3 _max_point) {
	min_point = _min_point;
	max_point = _max_point;
	
	x_min = min_point.x;
	y_min = min_point.y;
	z_min = min_point.z;
	
	x_max = max_point.x;
	y_max = max_point.y;
	z_max = max_point.z;
}

bool BVH_Box::rayIntersect(Ray &ray, float &t) {
	
	// Rays direction ando position origin.
	float3 ray_origin = ray.e();
	float3 ray_direction = ray.d();
	
	// The three coordinates of the ray origin.
	float r_o_x = ray_origin.x;
	float r_o_y = ray_origin.y;
	float r_o_z = ray_origin.z;
	
	// the three coordinates of the ray direction.
	float r_d_x = ray_direction.x;
	float r_d_y = ray_direction.y;
	float r_d_z = ray_direction.z;
	
	
	// From the the book the intersection 
	// parameters.
	float tx_min, ty_min, tz_min;
	float tx_max, ty_max, tz_max;
	
	float a = 1.0/r_d_x;	
	if (a >= 0){
		tx_min = (x_min - r_o_x)*a;
		tx_max = (x_max - r_o_x)*a;
	}
	else{
		tx_min = (x_max - r_o_x)*a;
		tx_max = (x_min - r_o_x)*a;
	}
	
	float b = 1.0/r_d_y;
	if (b >= 0){
		ty_min = (y_min - r_o_y)*b;
		ty_max = (y_max - r_o_y)*b;
	}
	else{
		ty_min = (y_max - r_o_y)*b;
		ty_max = (y_min - r_o_y)*b;
	}
	
	float c = 1.0/r_d_z;
	if (c >= 0){
		tz_min = (z_min - r_o_z)*c;
		tz_max = (z_max - r_o_z)*c;
	}
	else{
		tz_min = (z_max - r_o_z)*c;
		tz_max = (z_min - r_o_z)*c;
	}
	
	float t0, t1;
	
	// find the largest entering t value	
	if (tx_min > ty_min){
		t0 = tx_min;
	}
	else{
		t0 = ty_min;
	}
	
	if (tz_min > t0){
		t0 = tz_min;
	}
	
	// find the smallest exiting t value
	if (tx_max < ty_max){
		t1 = tx_max;
	}
	else{
		t1 = ty_max;
	}
	
	if (tz_max < t1){
		t1 = tz_max;
	}
	
	if (t0 > 0.00001f){
		t = t0; // The ray hit outside.
	}
	else {
		t = t1; // The ray hit inside.
	}
	
	return (t0 <= t1 && t1 > 0.00001f);
}
