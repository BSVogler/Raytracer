/* 
 * File:   Sphere.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 4. Juli 2014, 19:25
 */

#include "Sphere.hpp"

std::pair<bool, glm::vec3> Sphere::intersect(Ray const& ray) const {
    glm::vec3 l = ray.origin - center;
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2.0f*(glm::dot(l,ray.direction));
    float c = glm::dot(l,l) - radius*radius;
    
    float det = b*b-4.0f*a*c;
    if (det>=0.0f) {//wenn es min. eine Lösung gibt
        float t1 = (-b-sqrt(det))/(2.0f*a);
        float t2 = (-b+sqrt(det))/(2.0f*a);
        
        if (t1 < t2)//nimm Punkt, welcher näher dran ist
            return std::make_pair(true, l-(ray.origin+ray.direction*t1));//use t1
        else 
            return std::make_pair(true, l-(ray.origin+ray.direction*t2));//use t2
    } else 
        return std::make_pair(false, ray.origin);//keine Lösung
}