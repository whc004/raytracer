#include "vec.h" 
#include "mat.h" 
#include <vector>
#include <stack>
#include <sstream>

using namespace std;

void matransform (stack<mat4> &transfstack, float* values) ;
void rightmultiply (const mat4 & M, stack<mat4> &transfstack) ;
bool readvals (stringstream &s, const int numvals, float* values) ;
void readfile (const char * filename) ;
