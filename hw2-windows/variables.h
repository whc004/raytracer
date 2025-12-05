#ifndef VARIABLES_H
#define VARIABLES_H
#ifdef MAINPROGRAM
#define EXTERN 
#else
#define EXTERN extern
#endif
//#include <glm/glm.hpp>
#include <vector>
#include "vec.h"
#include "mat.h"
using namespace std;
/*
typedef glm::mat3 mat3;
typedef glm::mat4 mat4;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
*/
using namespace std;

struct Intersection {
public:
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emission;
    float shininess;
    vec3 point;
    vec3 normal;
    float t;
    Intersection(vec3 ambient, vec3 diffuse, vec3 specular, vec3 emission, float shininess, vec3 point, vec3 normal, float t)
        : ambient(ambient), diffuse(diffuse), specular(specular), emission(emission), shininess(shininess), point(point), normal(normal), t(t) {};
};

struct Directional_Light {
    vec3 dir;
    vec3 color;
    Directional_Light(const vec3& dir, const vec3& color) : dir(dir), color(color) {}
};

struct Point_Light {
    vec3 pos;
    vec3 color;
    Point_Light(vec3 pos, vec3 color) :pos(pos), color(color) {};
};

struct Ray {
public:
    vec3 origin;
    vec3 direction;
    Ray(vec3 origin, vec3 direction) : origin(origin), direction(direction) {};
};

struct Triangle {
public:
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emission;
    float shininess;
    mat4 transform;
    vec3 v1, v2, v3;
    Triangle(vec3 ambient, vec3 diffuse, vec3 specular, vec3 emission, float shininess, const mat4& transform, const vec3& v1, const vec3& v2, const vec3& v3)
        : ambient(ambient), diffuse(diffuse), specular(specular), emission(emission), shininess(shininess), transform(transform), v1(v1), v2(v2), v3(v3) {}
};

struct Sphere {
public:
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emission;
    float shininess;
    mat4 transform;
    vec3 center;
    float radius;
    Sphere(vec3 ambient, vec3 diffuse, vec3 specular, vec3 emission, float shininess, const mat4& transform, const vec3& center, float radius)
        : ambient(ambient), diffuse(diffuse), specular(specular), emission(emission), shininess(shininess), transform(transform), center(center), radius(radius) {}
};

#ifdef MAINPROGRAM 
const string Default_output = "raytrace.png";
const int Default_maxDepth = 5;
vec3 eye, up, center;
int w = 0;
int h = 0;
float fovy = 90.0f;
int maxdepth = Default_maxDepth;
int numLights = 10, numUsed = 0;
int maxverts = 999999999;
vector<vec3> vertices;
vector <Directional_Light> Directional_lights;
vector <Point_Light> Point_lights;
vector <Triangle> eachTriangle;
vector <Sphere> eachSphere;
float curr_ambient[3] = { .2,.2,.2 };
float curr_diffuse[3], curr_specular[3], curr_emission[3];
float curr_shininess;
vec3 attenuation = vec3(1.0, 0.0, 0.0);
string fnm;
#else 
EXTERN  vec3 eye, up, center;
EXTERN  int w, h;
EXTERN  float fovy;
EXTERN  int maxdepth;
EXTERN  int numLights, numUsed;
EXTERN  int maxverts;
EXTERN  vector<vec3> vertices;
EXTERN  vector <Triangle> eachTriangle;
EXTERN  vector <Sphere> eachSphere;
EXTERN  vector <Directional_Light> Directional_lights;
EXTERN  vector <Point_Light> Point_lights;
EXTERN  float curr_ambient[3], curr_diffuse[3], curr_specular[3], curr_emission[3];
EXTERN  float curr_shininess;
EXTERN  vec3 attenuation;
EXTERN string fnm;
#endif 

#endif // VARIABLES_H