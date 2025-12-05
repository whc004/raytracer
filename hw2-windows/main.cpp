#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include "Transform.h"
#include <FreeImage.h>
#include <omp.h>



using namespace std ; 

#define MAINPROGRAM 
#include "variables.h" 
#include "readfile.h"
#include "display.h"


void saveScreenshot(string fname) {
    int pix = w * h;
    BYTE* pixels = new BYTE[3 * pix];

    
    vector<vec3> image = Raytrace(pix);
    // TODO convert result to pixels format
    for (int i = 0; i < pix; i++) {
            
            pixels[i * 3] = unsigned char((int)255 * image[i].z);
            pixels[i * 3 + 1] = unsigned  char((int)255 * image[i].y);
            pixels[i * 3 + 2] = unsigned  char((int)255 * image[i].x);
           
            
    }

    FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, w, h, w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);

    std::cout << "Saving screenshot: " << fname << "\n";

    FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);

    delete pixels;
}


void printVariables()
{
    cout << "Camera Settings:\n";
    cout << " Eye: " << eye.x << ", " << eye.y << ", " << eye.z << "\n";
    cout << " Up: " << up.x << ", " << up.y << ", " << up.z << "\n";
    cout << " Center: " << center.x << ", " << center.y << ", " << center.z << "\n";
    cout << " Window dimensions: " << w << "x" << h << "\n";
    cout << " Field of view (fovy): " << fovy << "\n\n";

    cout << "Directional Lights:\n";
    for (const auto& light : Directional_lights)
    {
        cout << " Direction: " << light.dir.x << ", " << light.dir.y << ", " << light.dir.z << "\n";
        cout << " Color: " << light.color.x << ", " << light.color.y << ", " << light.color.z << "\n\n";
    }

    cout << "Point Lights:\n";
    for (const auto& light : Point_lights)
    {
        cout << " Position: " << light.pos.x << ", " << light.pos.y << ", " << light.pos.z << "\n";
        cout << " Color: " << light.color.x << ", " << light.color.y << ", " << light.color.z << "\n\n";
    }

    cout << "Triangles:\n";
    for (const auto& triangle : eachTriangle)
    {
        cout << " Ambient: [" << triangle.ambient.x << ", " << triangle.ambient.y << ", " << triangle.ambient.z << "]\n";
        cout << " Diffuse: [" << triangle.diffuse.x << ", " << triangle.diffuse.y << ", " << triangle.diffuse.z << "]\n";
        cout << " Specular: [" << triangle.specular.x << ", " << triangle.specular.y << ", " << triangle.specular.z << "]\n";
        cout << " Emission: [" << triangle.emission.x << ", " << triangle.emission.y << ", " << triangle.emission.z << "]\n";
        cout << " Shininess: " << triangle.shininess << "\n";
        cout << " Vertices: V1[" << triangle.v1.x << ", " << triangle.v1.y << ", " << triangle.v1.z << "], "
            << "V2[" << triangle.v2.x << ", " << triangle.v2.y << ", " << triangle.v2.z << "], "
            << "V3[" << triangle.v3.x << ", " << triangle.v3.y << ", " << triangle.v3.z << "]\n\n";
        cout << " Transform Matrix:\n";
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                cout << triangle.transform.m[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    cout << "Total Triangles: " << eachTriangle.size() << "\n\n";

    cout << "Spheres:\n";
    for (const auto& sphere : eachSphere)
    {
        cout << " Ambient: [" << sphere.ambient.x << ", " << sphere.ambient.y << ", " << sphere.ambient.z << "]\n";
        cout << " Diffuse: [" << sphere.diffuse.x << ", " << sphere.diffuse.y << ", " << sphere.diffuse.z << "]\n";
        cout << " Specular: [" << sphere.specular.x << ", " << sphere.specular.y << ", " << sphere.specular.z << "]\n";
        cout << " Emission: [" << sphere.emission.x << ", " << sphere.emission.y << ", " << sphere.emission.z << "]\n";
        cout << " Shininess: " << sphere.shininess << "\n";
        cout << " Center: [" << sphere.center.x << ", " << sphere.center.y << ", " << sphere.center.z << "], Radius: " << sphere.radius << "\n\n";
        cout << " Transform Matrix:\n";
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                cout << sphere.transform.m[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    cout << "Total Spheres: " << eachSphere.size() << "\n";
}

int main(int argc, char* argv[]) {
    cout << "Start" << endl;
    cout << argv[1]<< endl;
    if (argc < 2) {    
        cerr << "Usage: transforms scenefile [grader input (optional)]\n"; 
        return 1;
    }

    FreeImage_Initialise();

    readfile(argv[1]) ; 
    if (fnm.empty())
        saveScreenshot(Default_output);
    else 
        saveScreenshot(fnm);
    FreeImage_DeInitialise();
    //printVariables();
    cout << " attenuation: [" << attenuation.x << ", " << attenuation.y << ", " << attenuation.z << "]\n";
   
    //getchar();
    return 0;
}
