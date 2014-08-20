/* 
 * File:   Sphere.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 4. Juli 2014, 19:25
 */

#include "Sphere.hpp"
#include <glm/glm.hpp>

std::pair<bool, Ray> Sphere::intersect(Ray const& ray) const {
    glm::vec3 OC{center-ray.origin};
    float a{glm::dot(ray.direction, ray.direction)};
    float b{2.0f*(glm::dot(OC,ray.direction))};
    float c{glm::dot(OC,OC) - radius*radius};
    
    float det = b*b-4.0f*a*c;
    if (det>=0.0f) {//wenn es min. eine Lösung gibt
        float sqrtdet(sqrt(det));
        float t1((-b - sqrtdet) / (2.0f*a));
        float t2((-b + sqrtdet) / (2.0f*a));
        
        if (t2 < t1)//nimm Punkt, welcher näher dran ist
            std::swap(t2,t1);
           
        if (t1<ray.distance && t1>=0) {//collide if nearest point in front of camera
            ray.distance=t1;
            auto i(ray.origin+ray.direction*t1);
            return std::make_pair(true, Ray(i,glm::normalize(i-center)));//use t1, normal is n=CI=I-C
        }
    }
    return std::make_pair(false, Ray());//keine Lösung
}