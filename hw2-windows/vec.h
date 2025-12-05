#ifndef VEC_H
#define VEC_H

#include <cmath>
using namespace std;
class vec3 {
public:
    float x, y, z;
    vec3() : x(0.0), y(0.0), z(0.0) {};
    vec3(float x, float y, float z) : x(x), y(y), z(z) {};
    vec3 operator+(const vec3& v) const;
    vec3 operator-(const vec3& v) const;
    vec3 operator*(float scalar) const;
    vec3 operator*(const vec3& v) const;
    vec3 normalize() const;
    
    float length();

    
    static vec3 cross(const vec3& a, const vec3& b);
    static vec3 min(const vec3& a, const vec3& b);
    static float dot(const vec3& a, const vec3& b);
};

class vec4 {
public:
    float x, y, z, w;

    vec4() : x(0.0), y(0.0), z(0.0),w(0.0) {};
    vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
    vec4 operator+(const vec4& v) const;
    vec4 operator-(const vec4& v) const;
    vec4 operator*(float scalar) const;
    vec4 normalize() const;

    static float dot(const vec4& a, const vec4& b);
};

#endif 
