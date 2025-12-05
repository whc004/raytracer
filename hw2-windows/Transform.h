#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "vec.h"
#include "mat.h"
using namespace std;

const float pi = 3.14159265f ;

class Transform  
{
public:
	Transform();
	virtual ~Transform();
    static mat3 rotate(const float degrees, const vec3& axis) ;
    static mat4 scale(const float &sx, const float &sy, const float &sz) ; 
    static mat4 translate(const float &tx, const float &ty, const float &tz);
};

#endif

