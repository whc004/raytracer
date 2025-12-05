#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include "Transform.h" 

using namespace std;
#include "variables.h" 
#include "readfile.h"
#include "vec.h" 
#include "mat.h" 



void matransform(stack<mat4>& transfstack, float* values) {
    mat4 transform = transfstack.top();
    vec4 valvec(values[0], values[1], values[2], values[3]);
    vec4 newval = transform * valvec;
    values[0] = newval.x;
    values[1] = newval.y;
    values[2] = newval.z;
    values[3] = newval.w;
}

void rightmultiply(const mat4& M, stack<mat4>& transfstack) {
    mat4& T = transfstack.top();
    T = T * M;
}

bool readvals(stringstream& s, int numvals, float* values) {
    for (int i = 0; i < numvals; i++) {
        s >> values[i];
        if (s.fail()) {
            cout << "Failed reading value " << i << " will skip\n";
            return false;
        }
    }
    return true;
}

void readfile(const char* filename)
{
    string str, cmd;
    ifstream in;
    in.open(filename);
    if (in.is_open()) {

        // I need to implement a matrix stack to store transforms.  
        // This is done using standard STL Templates 
        stack <mat4> transfstack;
        transfstack.push(mat4());  // identity

        getline(in, str);
        while (in) {
            if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
                // Ruled out comment and blank lines 

                stringstream s(str);
                s >> cmd;
                int i;
                float values[10]; // Position and color for light, colors for others
                // Up to 10 params for cameras.  
                bool validinput; // Validity of input 

                // Process the light, add it to database.
                // Lighting Command

                if (cmd == "directional" || cmd == "point")
                {
                    if (numUsed == numLights)
                    { // No more Lights
                        cerr << "Reached Maximum Number of Lights " << numUsed << " Will ignore further lights\n";
                    }
                    else
                    {
                        if (cmd == "directional")
                        {
                            validinput = readvals(s, 6, values);
                            if (validinput)
                            {
                                Directional_Light Dlight = Directional_Light(vec3(values[0], values[1], values[2]), vec3(values[3], values[4], values[5]));
                                Directional_lights.push_back(Dlight);
                            }
                        }
                        else
                        {
                            validinput = readvals(s, 6, values);
                            if (validinput)
                            {
                                Point_Light Plight = Point_Light(vec3(values[0], values[1], values[2]), vec3(values[3], values[4], values[5]));
                                Point_lights.push_back(Plight);
                            }
                        }
                    }
                }

                // Material Commands 
                // Ambient, diffuse, specular, shininess properties for each object.
                // Filling this in is pretty straightforward, so I've left it in 
                // the skeleton, also as a hint of how to do the more complex ones.
                // Note that no transforms/stacks are applied to the colors. 

                else if (cmd == "ambient") {
                    validinput = readvals(s, 3, values); // colors 
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            curr_ambient[i] = values[i];
                        }
                    }
                }
                else if (cmd == "diffuse") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            curr_diffuse[i] = values[i];
                        }
                    }
                }
                else if (cmd == "specular") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            curr_specular[i] = values[i];
                        }
                    }
                }
                else if (cmd == "emission") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            curr_emission[i] = values[i];
                        }
                    }
                }
                else if (cmd == "shininess") {
                    validinput = readvals(s, 1, values);
                    if (validinput) {
                        curr_shininess = values[0];
                    }
                }
                else if (cmd == "size") {
                    validinput = readvals(s, 2, values);
                    if (validinput) {
                        w = (int)values[0]; h = (int)values[1];
                    }
                }
                else if (cmd == "maxdepth") {
                    validinput = readvals(s, 1, values);
                    if (validinput) {
                        maxdepth = (int)values[0];
                    }
                }
                else if (cmd == "attenuation") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        attenuation.x = values[0];
                        attenuation.y = values[1];
                        attenuation.z = values[2];
                    }
                }
                else if (cmd == "camera") {
                    validinput = readvals(s, 10, values); // 10 values eye cen up fov
                    if (validinput) {
                        
                        eye = vec3(float(values[0]), float(values[1]), float(values[2]));
                        center = vec3(float(values[3]), float(values[4]), float(values[5]));


                        up = vec3(float(values[6]), float(values[7]), float(values[8]));
                        fovy = float(values[9]);
                    }
                }
                // Geometry
                else if (cmd == "sphere")
                {
                    validinput = readvals(s, 4, values);
                    if (validinput)
                    {
                        vec3 ambient = vec3(curr_ambient[0], curr_ambient[1], curr_ambient[2]);
                        vec3 diffuse = vec3(curr_diffuse[0], curr_diffuse[1], curr_diffuse[2]);
                        vec3 specular = vec3(curr_specular[0], curr_specular[1], curr_specular[2]);
                        vec3 emission = vec3(curr_emission[0], curr_emission[1], curr_emission[2]);
                        Sphere currObject = Sphere(ambient, diffuse, specular, emission, curr_shininess, transfstack.top(), vec3(values[0], values[1], values[2]), values[3]);

                        eachSphere.push_back(currObject);
                    }

                }
                else if (cmd == "tri")
                {
                    validinput = readvals(s, 3, values);
                    if (validinput)
                    {
                        vec3 ambient = vec3(curr_ambient[0], curr_ambient[1], curr_ambient[2]);
                        vec3 diffuse = vec3(curr_diffuse[0], curr_diffuse[1], curr_diffuse[2]);
                        vec3 specular = vec3(curr_specular[0], curr_specular[1], curr_specular[2]);
                        vec3 emission = vec3(curr_emission[0], curr_emission[1], curr_emission[2]);
                        unsigned int v1_value = static_cast<unsigned int>(values[0]);
                        unsigned int v2_value = static_cast<unsigned int>(values[1]);
                        unsigned int v3_value = static_cast<unsigned int>(values[2]);
                        Triangle currObject = Triangle(ambient, diffuse, specular, emission, curr_shininess, transfstack.top(), vertices[v1_value], vertices[v2_value], vertices[v3_value]);

                        eachTriangle.push_back(currObject);
                    }

                }
                else if (cmd == "vertex")
                {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        vertices.push_back(vec3(values[0], values[1], values[2]));
                    }
                }
                else if (cmd == "maxverts")
                {
                    validinput = readvals(s, 1, values);
                    if (validinput) {
                        maxverts = static_cast<int>(values[0]);
                    }
                }

                else if (cmd == "translate") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        
                        mat4 translation = Transform::translate((float)values[0], (float)values[1], (float)values[2]);
                        rightmultiply(translation, transfstack);

                    }
                }
                else if (cmd == "scale") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        
                        mat4 scaling = Transform::scale((float)values[0], (float)values[1], (float)values[2]);
                        rightmultiply(scaling, transfstack);

                    }
                }
                else if (cmd == "rotate") {
                    validinput = readvals(s, 4, values);
                    if (validinput) {
                        
                        vec3 axis = vec3((float)values[0], (float)values[1], (float)values[2]);
                        float angle = values[3];
                        mat3 rotateMat = Transform::rotate(angle, axis);
                        mat4 rotation = mat4();
                        for (int i = 0; i < 3; i++) 
                        {
                            for (int j = 0; j < 3; j++) 
                            {
                                rotation.m[i][j] = rotateMat.m[i][j];
                            }
                        }

                        rotation.m[3][3] = 1;

                        rightmultiply(rotation, transfstack);

                    }
                }
                else if (cmd == "output") {

                    s >> fnm;
                    
                }

                // I include the basic push/pop code for matrix stacks
                else if (cmd == "pushTransform") {
                    transfstack.push(transfstack.top());
                }
                else if (cmd == "popTransform") {
                    if (transfstack.size() <= 1) {
                        cerr << "Stack has no elements.  Cannot Pop\n";
                    }
                    else {
                        transfstack.pop();
                    }
                }

                else {
                    cerr << "Unknown Command: " << cmd << " Skipping \n";
                }
            }
            getline(in, str);
        }
 

    }
    else {
        cerr << "Unable to Open Input Data File " << filename << "\n";
        throw 2;
    }
}
