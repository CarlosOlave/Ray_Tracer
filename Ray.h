/*
 *  Ray.h
 *  Theme06_m01
 *
 *  Created by Carlos Olave on 12/11/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

#ifndef RAY_H
#define RAY_H

#include "parse.h"

class Ray {

private:
	float3 direction;
	float3 origin;
	
public:
	Ray(){}
	Ray(float3 _direction, float3 _origin);
	
	void SetDirection(float3 _direction);
	void SetOrigin(float3 _origin);
	float3 d() {return direction;}
	float3 e() {return origin;}
};

#endif