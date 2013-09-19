/*
 *  Surface.h
 *  Theme06_m01
 *
 *  Created by Carlos Olave on 12/19/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

#ifndef SURFACE_H
#define SURFACE_H

#include "parse.h"

class Surface {

public:
	// Determines if ray hits a given surface.
	virtual bool hit(Ray& ray, float t_min, float t_max, float time, iPoint &hit_point) = 0;	
	
	// Gets the bounding box of a surface.
	virtual BVH_Box getBoundingBox() = 0;
	
	virtual void setMaterialIndex(int index) = 0;
};

#endif 