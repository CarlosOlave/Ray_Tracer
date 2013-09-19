#ifndef PARSE_H
#define PARSE_H

#include <cstdlib>
#include <iostream>
#include "Mesh.h"

using namespace std;

struct float3 {
  float x,y,z;
};

struct iPoint {
	float3 p;
	float3 np;
	float3 diffuse;
	float3 specular;
	float3 ideal_specular;
	int material_index;
	float phong_exponent;
	float t;
	bool isValid;
};

inline istream &operator>>(istream &is, float3 &f) {
  return is>>f.x>>f.y>>f.z;
}
inline ostream &operator<<(ostream &os, float3 &f) {
  return os<<"<"<<f.x<<","<<f.y<<","<<f.z<<">";
}

class Parser {
 protected:
  virtual void sphere(float3 pos, float r) {}
  virtual void triangle(float3 p1, float3 p2, float3 p3) {}
  virtual void triangle(float3 p1, float3 p2, float3 p3, 
						float3 np1, float3 np2, float3 np3) {}
  virtual void plane(float3 n, float d) {}
  virtual void camera(float3 pos, float3 dir, float d, float iw, float ih, int pw, int ph) {}
  virtual void pointLight(float3 pos, float3 rgb) {}
  virtual void directionalLight(float3 dir, float3 rgb) {}
  virtual void ambientLight(float3 rgb) {}
  virtual void material(float3 diff, float3 spec, float r, float3 refl) {}

 public:
  virtual void parse(const char *file);
  void ReadObj(char* _name);
	void SetTriangle(std::vector<float3> &collection, std::vector<float3> &normalCollection);	
};

#endif
