#ifndef MAT_H
#define MAT_H

#include "vec.h" 

using namespace std;

class mat4 {
public:
    float m[4][4];
    // basic mat
    mat4();
    // for vec
    mat4(const vec4& col1, const vec4& col2, const vec4& col3, const vec4& col4);
    // for all value
    mat4(float value1, float value2, float value3, float value4,
        float value5, float value6, float value7, float value8,
        float value9, float value10, float value11, float value12,
        float value13, float value14, float value15, float value16);
    mat4 operator+(const mat4& other) const;
    mat4 operator-(const mat4& other) const;

    mat4 operator*(const mat4& other) const;
    vec4 operator*(const vec4& v) const;

    vec3 operator*(const vec3& v) const;
    // for multi constant
    mat4 operator*(float scalar) const;
    static vec3 multiply(const vec3& v, const mat4& m);
    static mat4 transpose(const mat4& m);
    static mat4 inverse(const mat4& other);
};

class mat3 {
public:
    float m[3][3];

    mat3();
    mat3(const vec3& col1, const vec3& col2, const vec3& col3);
    mat3(float value1, float value2, float value3,
        float value4, float value5, float value6,
        float value7, float value8, float value9);
    mat3 operator+(const mat3& other) const;
    mat3 operator-(const mat3& other) const;
    mat3 operator*(const mat3& other) const;
    vec3 operator*(const vec3& v) const;
    mat3 operator*(float scalar) const;
};

#endif 
