
#include "Transform.h"
#include <iostream>

mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
    vec3 normalized_axis = axis.normalize();
    float radians = degrees * pi / 180.0f;
    float zero = 0.0f;
    mat3 identity_mat = mat3();
    vec3 col1 = vec3(normalized_axis.x * normalized_axis.x, normalized_axis.x * normalized_axis.y, normalized_axis.x * normalized_axis.z);
    vec3 col2 = vec3(normalized_axis.x * normalized_axis.y, normalized_axis.y * normalized_axis.y, normalized_axis.y * normalized_axis.z);
    vec3 col3 = vec3(normalized_axis.x * normalized_axis.z, normalized_axis.y * normalized_axis.z, normalized_axis.z * normalized_axis.z);

    mat3 aaT = mat3(col1,col2,col3);

    mat3 A_star = mat3(vec3(zero, normalized_axis.z, -normalized_axis.y), vec3( -normalized_axis.z, zero, normalized_axis.x), vec3(normalized_axis.y, -normalized_axis.x, zero));
    mat3 ret = (identity_mat*(cos(radians))) + (aaT*(1 - cos(radians))) + (A_star*(sin(radians)));
    
    return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
    mat4 ret;
    float basic = 1.0f;
    float zero = 0.0f;
    ret = mat4(sx, zero, zero, zero, zero, sy, zero, zero, zero, zero, sz, zero, zero, zero, zero, basic);
    return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    mat4 ret;
    float basic = 1.0f;
    float zero = 0.0;
    ret = mat4(basic, zero, zero, zero , zero, basic, zero, zero , zero, zero, basic, zero, tx , ty, tz, basic);
    return ret;
}


Transform::Transform()  
{

}

Transform::~Transform()
{

}
