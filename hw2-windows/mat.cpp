#include "mat.h" 
#include <glm/glm.hpp>

mat4::mat4() {
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            this->m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

mat4::mat4(const vec4& col1, const vec4& col2, const vec4& col3, const vec4& col4) {
    m[0][0] = col1.x; m[0][1] = col2.x; m[0][2] = col3.x; m[0][3] = col4.x;
    m[1][0] = col1.y; m[1][1] = col2.y; m[1][2] = col3.y; m[1][3] = col4.y;
    m[2][0] = col1.z; m[2][1] = col2.z; m[2][2] = col3.z; m[2][3] = col4.z;
    m[3][0] = col1.w; m[3][1] = col2.w; m[3][2] = col3.w; m[3][3] = col4.w;
}

mat4::mat4(float value1, float value2, float value3, float value4,
    float value5, float value6, float value7, float value8,
    float value9, float value10, float value11, float value12,
    float value13, float value14, float value15, float value16) {
    m[0][0] = value1;  m[0][1] = value5;  m[0][2] = value9;  m[0][3] = value13;
    m[1][0] = value2;  m[1][1] = value6;  m[1][2] = value10; m[1][3] = value14;
    m[2][0] = value3;  m[2][1] = value7;  m[2][2] = value11; m[2][3] = value15;
    m[3][0] = value4;  m[3][1] = value8;  m[3][2] = value12; m[3][3] = value16;
}

mat3::mat3() {
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j) 
        {
            this->m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

mat3::mat3(const vec3& col1, const vec3& col2, const vec3& col3) {
    m[0][0] = col1.x; m[0][1] = col2.x; m[0][2] = col3.x;
    m[1][0] = col1.y; m[1][1] = col2.y; m[1][2] = col3.y;
    m[2][0] = col1.z; m[2][1] = col2.z; m[2][2] = col3.z;
}

mat3::mat3(float value1, float value2, float value3,
    float value4, float value5, float value6,
    float value7, float value8, float value9) {
    m[0][0] = value1; m[0][1] = value4; m[0][2] = value7;
    m[1][0] = value2; m[1][1] = value5; m[1][2] = value8;
    m[2][0] = value3; m[2][1] = value6; m[2][2] = value9;
}



mat4 mat4::operator+(const mat4& other) const {
    mat4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = m[i][j] + other.m[i][j];
        }
    }
    return result;
}

mat4 mat4::operator-(const mat4& other) const {
    mat4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = m[i][j] - other.m[i][j];
        }
    }
    return result;
}

mat4 mat4::operator*(const mat4& other) const {
    mat4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += m[i][k] * other.m[k][j];
            }
        }
    }
    return result;
}

vec4 mat4::operator*(const vec4& v) const {
    vec4 result(0, 0, 0, 0);
    result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
    result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
    result.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
    result.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;
    return result;
}

vec3 mat4::operator*(const vec3& v) const {
    vec3 result(0, 0, 0);
    result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * 1;
    result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * 1;
    result.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * 1;
    return result;
}

mat4 mat4::operator*(float scalar) const {
    mat4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = m[i][j] * scalar;
        }
    }
    return result;
}

mat4 mat4::transpose(const mat4& mat)
{
    glm::mat4 Inversemat4(mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[3][0],
        mat.m[0][1], mat.m[1][1], mat.m[2][1], mat.m[3][1],
        mat.m[0][2], mat.m[1][2], mat.m[2][2], mat.m[3][2],
        mat.m[0][3], mat.m[1][3], mat.m[2][3], mat.m[3][3]);
    Inversemat4 = glm::transpose(Inversemat4);
    /*
    mat4 result(Inversemat4[0][0], Inversemat4[1][0], Inversemat4[2][0], Inversemat4[3][0],
        Inversemat4[0][1], Inversemat4[1][1], Inversemat4[2][1], Inversemat4[3][1],
        Inversemat4[0][2], Inversemat4[1][2], Inversemat4[2][2], Inversemat4[3][2],
        Inversemat4[0][3], Inversemat4[1][3], Inversemat4[2][3], Inversemat4[3][3]);
*/
    mat4 result(Inversemat4[0][0], Inversemat4[0][1], Inversemat4[0][2], Inversemat4[0][3],
        Inversemat4[1][0], Inversemat4[1][1], Inversemat4[1][2], Inversemat4[1][3],
        Inversemat4[2][0], Inversemat4[2][1], Inversemat4[2][2], Inversemat4[2][3],
        Inversemat4[3][0], Inversemat4[3][1], Inversemat4[3][2], Inversemat4[3][3]);
    return result;

}

vec3 mat4::multiply(const vec3& v, const mat4& m) {
    vec4 res = m * vec4(v.x, v.y, v.z, 1.0f);
    return vec3(res.x / res.w, res.y / res.w, res.z / res.w);
}



mat4 mat4::inverse(const mat4& mat)
{
    glm::mat4 Inversemat4(mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[3][0],
        mat.m[0][1], mat.m[1][1], mat.m[2][1], mat.m[3][1],
        mat.m[0][2], mat.m[1][2], mat.m[2][2], mat.m[3][2],
        mat.m[0][3], mat.m[1][3], mat.m[2][3], mat.m[3][3]);
    Inversemat4 = glm::inverse(Inversemat4);
    /*
    mat4 result(Inversemat4[0][0], Inversemat4[1][0], Inversemat4[2][0], Inversemat4[3][0],
        Inversemat4[0][1], Inversemat4[1][1], Inversemat4[2][1], Inversemat4[3][1],
        Inversemat4[0][2], Inversemat4[1][2], Inversemat4[2][2], Inversemat4[3][2],
        Inversemat4[0][3], Inversemat4[1][3], Inversemat4[2][3], Inversemat4[3][3]);
*/
    mat4 result(Inversemat4[0][0], Inversemat4[0][1], Inversemat4[0][2], Inversemat4[0][3],
        Inversemat4[1][0], Inversemat4[1][1], Inversemat4[1][2], Inversemat4[1][3],
        Inversemat4[2][0], Inversemat4[2][1], Inversemat4[2][2], Inversemat4[2][3],
        Inversemat4[3][0], Inversemat4[3][1], Inversemat4[3][2], Inversemat4[3][3]);
    return result;



}





mat3 mat3::operator+(const mat3& other) const {
    mat3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.m[i][j] = m[i][j] + other.m[i][j];
        }
    }
    return result;
}

mat3 mat3::operator-(const mat3& other) const {
    mat3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.m[i][j] = m[i][j] - other.m[i][j];
        }
    }
    return result;
}

mat3 mat3::operator*(const mat3& other) const {
    mat3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.m[i][j] = 0;
            for (int k = 0; k < 3; ++k) {
                result.m[i][j] += m[i][k] * other.m[k][j];
            }
        }
    }
    return result;
}

vec3 mat3::operator*(const vec3& v) const {
    vec3 result(0, 0, 0);
    result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
    result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
    result.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;
    return result;
}

mat3 mat3::operator*(float scalar) const {
    mat3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.m[i][j] = m[i][j] * scalar;
        }
    }
    return result;
}

