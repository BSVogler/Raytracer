/* 
 * File:   Sphere.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 4. Juli 2014, 19:25
 */

#include "Sphere.hpp"
#include "Intersection.hpp"
#include <glm/glm.hpp>

Intersection Sphere::intersect(Ray const& ray) const {
    Ray ray_t;
    if (isTransformed())
        ray_t = Ray(
            glm::vec3(getWorldTransfInv() * glm::vec4(ray.origin, 1)),
            glm::vec3(getWorldTransfInv() * glm::vec4(ray.direction, 0))
        );
    else
        ray_t = Ray(ray);

    glm::vec3 CO{ ray_t.origin - center };//why CO and not OC???
    float a{ glm::dot(ray_t.direction, ray_t.direction) };
    float b{ 2.0f * glm::dot(CO, ray_t.direction) };
    float c{ glm::dot(CO,CO) - radius*radius};
    
    float det = b*b - 4.0f*a*c;
    if (det >= 0.0f) {//wenn es min. eine Lösung gibt
        float sqrtdet(sqrt(det));
        float t1((-b - sqrtdet) / (2.0f*a));
        float t2((-b + sqrtdet) / (2.0f*a));
        
        if (t2 < t1)//nimm Punkt, welcher näher dran ist
            std::swap(t2,t1);
        
        if (t1<ray.mint ||t1>ray.maxt)//filter
            return Intersection();  
            
        Intersection inter;
        inter.hit = true;
        inter.ray.origin = ray_t.origin+ray_t.direction*t1;
        //use t1, normal is n=CI=I-C, same as CO+i
        //then multiplay with transformationmatrix, inverse transponed
        inter.ray.direction = glm::normalize(inter.ray.origin-center);
        if (isTransformed()) inter.ray.direction = getWorldTransfInvTransp()*inter.ray.direction;
        
        inter.distance= t1;
        inter.material = getMaterial();
        return inter;
    }
    return Intersection(); 
}