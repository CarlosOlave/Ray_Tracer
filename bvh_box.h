/*
 *  bvh_box.h
 *  Theme06_m01
 *
 *  Created by Carlos Olave on 12/18/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

#ifndef BVH_BOX
#define BVH_BOX

#include "parse.h"
#include "Ray.h"

// The class representing the bounding box for the 
// Bounding Volume Hierarchy.
class BVH_Box {
	
private:
	float3 min_point;
	float3 max_point;
	
	float x_min, y_min, z_min;
	float x_max, y_max, z_max;
	
public:
	BVH_Box();
	BVH_Box(float3 _min_point, float3 _max_point);
	bool rayIntersect(Ray & ray, float &t);
	
	float3 getMinPoint() {return min_point;}	
	float3 getMaxPoint() {return max_point;}
};

inline BVH_Box boundBox (BVH_Box &box_a, BVH_Box &box_b) {
	
	float3 box_min_point, box_max_point;
	
	// Compute the min point.
	box_min_point.x = (box_a.getMinPoint().x < box_b.getMinPoint().x? box_a.getMinPoint().x : box_b.getMinPoint().x);
	box_min_point.y = (box_a.getMinPoint().y < box_b.getMinPoint().y? box_a.getMinPoint().y : box_b.getMinPoint().y);
	box_min_point.z = (box_a.getMinPoint().z < box_b.getMinPoint().z? box_a.getMinPoint().z : box_b.getMinPoint().z);
	
	// Compute the max point.
	box_max_point.x = (box_a.getMaxPoint().x > box_b.getMaxPoint().x? box_a.getMaxPoint().x : box_b.getMaxPoint().x);
	box_max_point.y = (box_a.getMaxPoint().y > box_b.getMaxPoint().y? box_a.getMaxPoint().y : box_b.getMaxPoint().y);
	box_max_point.z = (box_a.getMaxPoint().z > box_b.getMaxPoint().z? box_a.getMaxPoint().z : box_b.getMaxPoint().z);
	
	
	// Returns a new box bounded box.
	return BVH_Box(box_min_point, box_max_point); 
}

#endif