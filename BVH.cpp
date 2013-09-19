/*
 *  BVH.cpp
 *  Theme06_m01
 *
 *  Created by Carlos Olave on 12/18/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

#include "BVH.h"

// Initialize construtor for left and right branch, and boundig box.
BVH::BVH(Surface* l, Surface* r, BVH_Box &b) {
	left = l;
	right = r;
	bvh_box = b;
}

BVH::BVH(Surface* l, Surface* r) {
	left = l;
	right = r;
	BVH_Box lb = l->getBoundingBox();
	BVH_Box rb = r->getBoundingBox();
	bvh_box = boundBox(lb, rb);
}

BVH::BVH(Surface* l) {
	left = l;
	right = NULL;
	BVH_Box lb = l->getBoundingBox();
	bvh_box = boundBox(lb, lb);
}

BVH::BVH(Surface** s_col, int s_col_size) {

	if (s_col_size == 0) return;
	if (s_col_size == 1) {
		*this = BVH(s_col[0]);
		return;
	}
	if (s_col_size == 2) {
		*this = BVH(s_col[0], s_col[1]);
		return;
	}
	
	// find the midpoint of the bounding box to use as a split
	bvh_box = s_col[0]->getBoundingBox();
	BVH_Box temp_box;
	for (int i=1; i<s_col_size; i++) {
		temp_box = s_col[i]->getBoundingBox();
		bvh_box = boundBox(bvh_box, temp_box);
	}
	
	float3 pivot_point = ((bvh_box.getMaxPoint() + bvh_box.getMinPoint())/2.0f);
	
	int split_mid_point = splitCollection(s_col, s_col_size, pivot_point.x, 0);
	
	// Create the new branches for this BVH
	left = buildBranch(s_col, split_mid_point, 1);
	right = buildBranch(&s_col[split_mid_point], s_col_size-split_mid_point, 1);	
}

Surface* BVH::buildBranch(Surface** s_col, int col_size, int axis) {

	if (col_size == 1) return s_col[0];
	if (col_size == 2) return new BVH(s_col[0], s_col[1]);
	
	BVH_Box my_box = s_col[0]->getBoundingBox();
	BVH_Box temp_box;
	for (int i=1; i<col_size; i++) {	
		temp_box = s_col[i]->getBoundingBox();
		my_box = boundBox(my_box, temp_box);
	}
	
	float3 split_pivot = ((my_box.getMaxPoint() + my_box.getMinPoint())/2.0f);
	
	int pivot_axis_value = 0;
	if (axis == 0)
		pivot_axis_value = split_pivot.x;
	else if (axis == 1)
		pivot_axis_value = split_pivot.y;
	else 
		pivot_axis_value = split_pivot.z;
	
	
	int mid_point = splitCollection(s_col, col_size, pivot_axis_value, axis);

	Surface* s_left = buildBranch(s_col, mid_point, (axis + 1) % 3);
	Surface* s_right = buildBranch(&s_col[mid_point], col_size-mid_point, (axis+1)%3);
	
	return new BVH(s_left, s_right, my_box);
}

bool BVH::clean() {
	delete left;
	left = NULL;
	delete right;
	right = NULL;
	
	return true;
}

// Virtual functions.

bool BVH::hit(Ray &ray, float t_min, float t_max, float time, iPoint &hit_point) {

	// Check wheter the ray hits the bounding box.
	if (!bvh_box.rayIntersect(ray, t_min)) return false;
	
	// If we do a hit the bounding box then we need
	// to check both branches.
	bool isLeftHit = false;
	bool isRightHit = false;
	
	iPoint l_hit_point, r_hit_point;
	
	if (right != NULL)
		isRightHit = right->hit(ray, t_min, t_max, time, r_hit_point);
	
	if (left != NULL)
		isLeftHit = left->hit(ray, t_min, hit_point.t, time, l_hit_point);
	
	if (isRightHit && isLeftHit) {
		if (l_hit_point.t < r_hit_point.t)
			hit_point = l_hit_point;
		else 
			hit_point = r_hit_point;
		return true;
	}
	else if (isLeftHit) {
		hit_point = l_hit_point;
		return true;
	}
	else if (isRightHit) {
		hit_point = r_hit_point;
		return true;
	}
	else {
		return false;
	}
	//return (isRightHit || isLeftHit);
}

BVH_Box BVH::getBoundingBox() {
	return bvh_box;
}

void BVH::setMaterialIndex(int index) {
	return;
}