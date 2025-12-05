// Basic includes to get this file to work.  
#include "display.h"



Ray RayThruPixel(int x, int y) {

    float cal_fovy = fovy * pi / 180.0f;
    float fovx = tan(cal_fovy / 2.0f) * float(w) / float(h);
    float alpha = fovx * ((float(y + 0.5f) - w / 2.0f) / (w / 2.0f));
    float beta = tan(cal_fovy / 2.0f) * ((h / 2.0f) - float(x + 0.5f)) / (h / 2.0f);


    vec3 a = eye - center;
    vec3 w_vector = a.normalize();
    vec3 cross = vec3::cross(up, w_vector);
    vec3 u = cross.normalize();
    vec3 v = vec3::cross(w_vector, u);

    Ray r(eye, u * alpha + v * beta - w_vector);
    return r;
}


float IntersectSphere(Ray r, Sphere* sphere) {
    mat4 Transform = mat4(sphere->transform);
    mat4 I_Transform = mat4::inverse(Transform);

    // in homogeneous coordinate
    vec4 Orign_4 = I_Transform * vec4(r.origin.x, r.origin.y, r.origin.z, 1.0);
    vec4 Direction_4 = I_Transform * vec4(r.direction.x, r.direction.y, r.direction.z, 0.0);
    vec3 Orign = vec3(Orign_4.x / Orign_4.w, Orign_4.y / Orign_4.w, Orign_4.z / Orign_4.w);
    vec3 Direction = vec3(Direction_4.x, Direction_4.y, Direction_4.z);

    //the equation of P
    float A = vec3::dot(Direction, Direction);
    float B = 2 * vec3::dot(Direction, Orign - sphere->center);
    float C = vec3::dot(Orign - sphere->center, Orign - sphere->center) - (sphere->radius * sphere->radius);
    float d = B * B - 4 * A * C;

    if (d < 0.0f)
    {
        return -1.0f;
    }
    else if (d < 0.001)
    {
        float t = -B / (2 * A);
        vec3 p = Orign + Direction * t;
        vec4 Actual_Point_4 = Transform * vec4(p.x, p.y, p.z, 1);
        vec3 Actual_Point = vec3(Actual_Point_4.x, Actual_Point_4.y, Actual_Point_4.z);
        return t;
    }
    else
    {
        float t1 = (-B + sqrt(d)) / (2 * A);
        float t2 = (-B - sqrt(d)) / (2 * A);
        vec3 p_1 = Orign + Direction * t1;
        vec4 Actual_Point_4_1 = Transform * vec4(p_1.x, p_1.y, p_1.z, 1);
        vec3 Actual_Point_1 = vec3(Actual_Point_4_1.x, Actual_Point_4_1.y, Actual_Point_4_1.z);
        vec3 p_2 = Orign + Direction * t2;
        vec4 Actual_Point_4_2 = Transform * vec4(p_2.x, p_2.y, p_2.z, 1);
        vec3 Actual_Point_2 = vec3(Actual_Point_4_2.x, Actual_Point_4_2.y, Actual_Point_4_2.z);
        return min(t1, t2);
    }
}


float IntersectTriangle(Ray r, Triangle* tri) {
    //vec3 n = vec3::cross((tri->v3 - tri->v1), (tri->v2 - tri->v1)).normalize();

    //float t = (vec3::dot((tri->v1 - eye), n) - vec3::dot(r.origin, n)) / vec3::dot(r.direction, n);
    ;
    //vec3 P = r.origin + r.direction * t;

    vec3 A = tri->transform * tri->v1;
    vec3 B = tri->transform * tri->v2;
    vec3 C = tri->transform * tri->v3;

    vec3 n = vec3::cross((C - A), (B - A)).normalize();
    float t = (vec3::dot(A, n) - vec3::dot(r.origin, n)) / vec3::dot(r.direction, n);
    vec3 p = r.origin + r.direction * t;

    /*
    vec3 c0 = vec3::cross(tri->v2 - tri->v1, P - tri->v1);
    vec3 c1 = vec3::cross(tri->v3 - tri->v2, P - tri->v2);
    vec3 c2 = vec3::cross(tri->v1 - tri->v3, P - tri->v3);
    */
    if (HitInTriangle(p, A, B, C)) {
        return t;
    }
    return -1.0f;
}

// Use Barycentric coordinate take find out whether point inside the Triangle
bool HitInTriangle(vec3 P, vec3 A, vec3 B, vec3 C) {

    vec3 PA = P - A;
    vec3 PB = P - B;
    vec3 PC = P - C;

    vec3 AB = B - A;
    vec3 BC = C - B;
    vec3 AC = C - A;

    float areaPAB = (vec3::cross(PA, PB)).length();
    float areaPBC = (vec3::cross(PB, PC)).length();
    float areaPAC = (vec3::cross(PA, PC)).length();

    float areaABC = (vec3::cross(AB, AC)).length();

    float alpha = areaPBC / areaABC;
    float beta = areaPAC / areaABC;
    float gamma = areaPAB / areaABC;

    return 1.00001f > alpha > -0.00001f && 1.00001f > beta > -0.00001f && 1.00001f > gamma > -0.00001f && (0.99999f < (alpha + beta + gamma)) && ((alpha + beta + gamma) < 1.00001f);
}

Intersection FindIntersect(Ray r, vector<Sphere> sceneSphere, vector<Triangle> sceneTriangle, bool* isTri) {
    float min_T = INFINITY;

    *isTri = false;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emission;
    float shininess = 0.0f;
    vec3 point;
    mat4 transform;
    vec3 center;
    vec3 a, b, c;


    for (int i = 0; i < sceneSphere.size(); ++i) {
        // if intersects and is less than minT
        float temp_T = IntersectSphere(r, &sceneSphere[i]);
        if (temp_T > 0 && min_T > temp_T)
        {
            min_T = temp_T;
            ambient = sceneSphere[i].ambient;
            diffuse = sceneSphere[i].diffuse;
            specular = sceneSphere[i].specular;
            emission = sceneSphere[i].emission;
            shininess = sceneSphere[i].shininess;
            point = r.origin + r.direction * min_T;
            transform = sceneSphere[i].transform;
            center = sceneSphere[i].center;
        }
    }

    for (int i = 0; i < sceneTriangle.size(); ++i) {
        float temp_T = IntersectTriangle(r, &sceneTriangle[i]);
        if (temp_T > 0 && min_T > temp_T)
        {
            min_T = temp_T;
            *isTri = true;
            ambient = sceneTriangle[i].ambient;
            diffuse = sceneTriangle[i].diffuse;
            specular = sceneTriangle[i].specular;
            emission = sceneTriangle[i].emission;
            shininess = sceneTriangle[i].shininess;
            point = r.origin + r.direction * min_T;
            transform = sceneTriangle[i].transform;
            a = sceneTriangle[i].v1;
            b = sceneTriangle[i].v2;
            c = sceneTriangle[i].v3;
        }
    }



    vec3 normal;
    if (*isTri) {
        vec3 locnorm = vec3::cross(b - a, c - a).normalize();

        mat4 invTrans = mat4::transpose(mat4::inverse(transform));
        normal = mat4::multiply(locnorm, invTrans).normalize();
    }
    else {
        mat4 inv = mat4::inverse(transform);
        vec3 p = mat4::multiply(point, inv);
        vec3 pmc = p - center;
        vec4 ans = mat4::transpose(inv) * vec4(pmc.x, pmc.y, pmc.z, 0.0f);
        normal = vec3(ans.x, ans.y, ans.z).normalize();
    }

    return Intersection(ambient, diffuse, specular, emission, shininess, point, normal, min_T);

}
/*
* 
* vec4 ComputeLight (vec3 direction, vec4 lightcolor, vec3 normal, vec3 halfvec, vec4 mydiffuse, vec4 myspecular, float myshininess) {

        float nDotL = dot(normal, direction)  ;         
        vec4 lambert = mydiffuse * lightcolor * max (nDotL, 0.0) ;  

        float nDotH = dot(normal, halfvec) ; 
        vec4 phong = myspecular * lightcolor * pow (max(nDotH, 0.0), myshininess) ; 

        vec4 retval = lambert + phong ; 
        return retval ;
}  
* 
* 
* if (lightposn[i].w == 0)
            {
                //directional light
                vec3 direction = normalize(lightposn[i].xyz);
                vec3 halfvec = normalize(direction + eyedirn);
                finalcolor += ComputeLight(direction, lightcolor[i], normal, halfvec, diffuse, specular, shininess);
            }
            else
            {
                vec3 lightPosition = (lightposn[i].xyz / lightposn[i].w);
                vec3 direction = normalize(lightPosition - mypos);
                vec3 halfvec = normalize(direction + eyedirn);
                finalcolor += ComputeLight(direction, lightcolor[i], normal, halfvec, diffuse, specular, shininess);
            }
*/
vec3 ComputeDirLight(Directional_Light light, Intersection hit, Ray ray) {
    
    vec3 direction = light.dir.normalize();

    float nDotL = std::max(vec3::dot(hit.normal.normalize(), direction), 0.0f);
    vec3 lambert = hit.diffuse * light.color * nDotL;

    vec3 halfvec = (direction + (ray.direction)).normalize();
    float nDotH = std::max(vec3::dot(hit.normal.normalize(), halfvec), 0.0f);
    vec3 phong = hit.specular * light.color * pow(nDotH, hit.shininess);

    vec3 result = lambert + phong;
    return result;
}

vec3 ComputePntLight(Point_Light light, Intersection hit, Ray ray, vec3 atten) {



    float nDotL = std::max(vec3::dot(hit.normal.normalize(), (light.pos - hit.point).normalize()), 0.0f);
    vec3 lambert = hit.diffuse * light.color * nDotL;

    vec3 halfvec = ((light.pos - hit.point).normalize() + (ray.origin - hit.point).normalize()).normalize();
    float nDotH = std::max(vec3::dot(hit.normal.normalize(), halfvec), 0.0f);
    vec3 phong = hit.specular * light.color * pow(nDotH, hit.shininess);

    vec3 result = lambert + phong;

    float r = (light.pos - hit.point).length();

    result = result * (1.0 / (atten.x + atten.y * r + atten.z * r * r));

    return result;
}

vec3 FindColor(Intersection hit, Ray r, bool isTri, int depth)
{
    vec3 result = vec3(hit.ambient + hit.emission);

    // directional
    for (int i = 0; i < Directional_lights.size(); ++i)
    {
        result = result + ComputeDirLight(Directional_lights[i], hit, r);
    }

    // point lights

    for (int i = 0; i < Point_lights.size(); ++i)
    {
        Ray lightray(Point_lights[i].pos, hit.point - Point_lights[i].pos);
        bool temp;

        Intersection light_hit = FindIntersect(lightray, eachSphere, eachTriangle, &temp);

        bool v =  light_hit.t < INFINITY;

        if (v && abs(hit.point.x - light_hit.point.x) < 0.001f && abs(hit.point.y - light_hit.point.y) < 0.001f && abs(hit.point.z - light_hit.point.z) < 0.001f) {
            result = result + ComputePntLight(Point_lights[i], hit, r, attenuation);

        }
    }

    if (hit.specular.x != 0.0f || hit.specular.y != 0.0f || hit.specular.z != 0.0f) {
        vec3 epsilon = hit.normal.normalize() * 0.0001f;
        Ray ref = Ray(hit.point + epsilon, r.direction.normalize() - (hit.normal.normalize() * (2 * vec3::dot(r.direction.normalize(), hit.normal.normalize()))));

        vec3 color = CalculateColor(ref, depth + 1);
        result = result + hit.specular * color;
    }


    return vec3::min(result, vec3(1.0f, 1.0f, 1.0f));
}


vec3 CalculateColor(Ray ray, int depth) {

    if (depth >= maxdepth)
        return vec3(0, 0, 0);

    bool isTri;
    Intersection hit = FindIntersect(ray, eachSphere, eachTriangle, &isTri);

    if (hit.t > 0 && hit.t < INFINITY)
        return FindColor(hit, ray, isTri, depth);

    return vec3(0, 0, 0);
}


vector<vec3> Raytrace(int pix)
{
    vector<vec3> image(pix);

#pragma omp parallel for
    for (int i = 0; i < h; i++) {
#pragma omp parallel for
        for (int j = 0; j < w; j++) {
            Ray ray = RayThruPixel(i, j);
            image[i * w + j] = CalculateColor(ray, 0);
        }
    }

    return image;

}
