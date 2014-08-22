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
    glm::vec3 CO{ ray.origin - center };//why CO and not OC???
    float a{ glm::dot(ray.direction, ray.direction) };
    float b{ 2.0f * glm::dot(CO, ray.direction) };
    float c{ glm::dot(CO,CO) - radius*radius};
    
    float det = b*b - 4.0f*a*c;
    if (det >= 0.0f) {//wenn es min. eine Lösung gibt
        float sqrtdet(sqrt(det));
        float t1((-b - sqrtdet) / (2.0f*a));
        float t2((-b + sqrtdet) / (2.0f*a));
        
        if (t2 < t1)//nimm Punkt, welcher näher dran ist
            std::swap(t2,t1);
        
        if (t1>=0) {//collide if nearest point in front of camera
            ray.distance=t1;
            auto p(ray.origin+ray.direction*t1);
            Intersection inter;
            inter.hit = true;
            inter.ray.origin = p;
            inter.ray.direction = glm::normalize(p-center);//use t1, normal is n=CI=I-C, same as CO+i
            inter.material = getMaterial();
            return inter;
        }
    }
    return Intersection();//keine Lösung
}