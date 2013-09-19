/*
 *  Ray.cpp
 *  Theme06_m01
 *
 *  Created by Carlos Olave on 12/11/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

#include "Ray.h"

Ray::Ray(float3 _direction, float3 _origin) {
	direction = _direction;
	origin = _origin;
}

void Ray::SetDirection(float3 _direction) {
	direction = _direction;
}

void Ray::SetOrigin(float3 _origin) {
	origin = _origin;
}