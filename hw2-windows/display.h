#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <omp.h>
#include "vec.h"
#include "mat.h"
#include "Transform.h"
#include <glm/glm.hpp>

using namespace std;
#include "variables.h"
#include "readfile.h"


Ray RayThruPixel(int x, int y);


float IntersectSphere(Ray r, Sphere* sphere);

float IntersectTriangle(Ray r, Triangle* tri);

bool HitInTriangle(vec3 P, vec3 A, vec3 B, vec3 C);

Intersection FindIntersect(Ray r, vector<Sphere> sceneSphere, vector<Triangle> sceneTriangle, bool* isTri);


vec3 ComputeDirLight(Directional_Light light, Intersection hit, Ray ray);

vec3 ComputePntLight(Point_Light light, Intersection hit, Ray ray, float atten[3]);

vec3 FindColor(Intersection hit, Ray r, bool isTri, int depth);


vec3 CalculateColor(Ray ray, int depth);


vector<vec3> Raytrace(int pix);

#endif
