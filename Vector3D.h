#ifndef _VECTOR3D_H_
#define _VECTOR3D_H_
#include <cmath>
#include <assert.h>

class Vector3D {
public:
	float x, y, z;
	Vector3D(float xx = 0.0, float yy = 0.0, float zz = 0.0):x(xx), y(yy), z(zz){}
	inline operator float *() {return &x;}
	float Length(){return sqrt(x * x + y * y + z * z);}
};

Vector3D normalize (Vector3D& v);

Vector3D operator+ (const Vector3D& v1, const Vector3D& v2);
Vector3D operator- (const Vector3D& v);

Vector3D operator- (const Vector3D& v1, const Vector3D& v2);
Vector3D operator* (const Vector3D& v1, float l);
Vector3D operator/ (const Vector3D& v1, float l);
float  operator^ (const Vector3D& v1, const Vector3D& v2);//dot product
Vector3D operator* (const Vector3D& v1, const Vector3D& v2);//cross product

#endif
