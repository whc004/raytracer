#include "vec.h"


vec3 vec3::operator+(const vec3& v) const {
    return vec3(x + v.x, y + v.y, z + v.z);
}

vec3 vec3::operator-(const vec3& v) const {
    return vec3(x - v.x, y - v.y, z - v.z);
}


vec3 vec3::operator*(float scalar) const {
    return vec3(x * scalar, y * scalar, z * scalar);
}

vec3 vec3::operator*(const vec3& v) const {
    return vec3(x * v.x, y * v.y, z * v.z);
}

vec3 vec3::normalize() const {
    float length = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    return vec3(this->x / length, this->y / length, this->z / length);
}

float vec3::length() {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

vec3 vec3::cross(const vec3& a, const vec3& b) {
    return vec3(a.y * b.z - a.z * b.y,
        b.x * a.z - b.z * a.x ,
        a.x * b.y - a.y * b.x);
}

vec3 vec3::min(const vec3& a, const vec3& b) {
    if (sqrt(a.x * a.x + a.y * a.y + a.z * a.z) > sqrt(b.x * b.x + b.y * b.y + b.z * b.z))
        return b;
    return a;
}




float vec3::dot(const vec3& a, const vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}


vec4 vec4::operator+(const vec4& v) const {
    return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
}

vec4 vec4::operator-(const vec4& v) const {
    return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
}

vec4 vec4::operator*(float scalar) const {
    return vec4(x * scalar, y * scalar, z * scalar, w * scalar);
}

vec4 vec4::normalize() const {
    float length = sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
    return vec4(this->x / length, this->y / length, this->z / length, this->w / length);
}


float vec4::dot(const vec4& a, const vec4& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
