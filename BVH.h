/*
 *  BVH.h
 *  Theme06_m01
 *
 *  Created by Carlos Olave on 12/18/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */


#ifndef BVH_H
#define BVH_H

#include "bvh_box.h"
#include "Objects.h"
#include "Surface.h"

class BVH : public Surface {
	
private:
	BVH_Box bvh_box;
	Surface* left;
	Surface* right;
	
public:
	BVH(){}
	BVH(Surface* l, Surface* r, BVH_Box &b);
	BVH(Surface* l);
	BVH(Surface* l, Surface* r);
	BVH(Surface** s_col, int s_col_size);
	Surface* buildBranch(Surface** s_col, int collection_size, int axis);
	bool clean();
	
	// Virtual functions implemented.
	bool hit(Ray &ray, float t_min, float t_max, float time, iPoint &hit_point);
	BVH_Box getBoundingBox();
	void setMaterialIndex(int index);
};

inline int splitCollection(Surface** s_col, int s_size, float pivot, int axis) {
	BVH_Box my_box;
	float center;
	int split_val = 0;
	
	for (int i = 0; i < s_size; i++)
	{
		my_box = s_col[i]->getBoundingBox();
		
		if (axis == 0)
			center = ((my_box.getMinPoint().x + my_box.getMaxPoint().x)/2.0f);
		else if (axis == 1)
			center = ((my_box.getMinPoint().y + my_box.getMaxPoint().y)/2.0f);
		else 
			center = ((my_box.getMinPoint().z + my_box.getMaxPoint().z)/2.0f);
		
		if (center < pivot)
		{
			Surface* temp = s_col[i];
			s_col[i] = s_col[split_val];
			s_col[split_val] = temp;
			split_val++;
		}
	}
	
	if (split_val == 0 || split_val == s_size) split_val = s_size/2;
	
	return split_val;
}

#endif

