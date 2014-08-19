/* 
 * File:   Sphere.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 4. Juli 2014, 19:25
 */

#include "Sphere.hpp"
#include <glm/glm.hpp>

std::pair<bool, Ray> Sphere::intersect(Ray const& ray) const {
    glm::vec3 l{ray.origin - center};
    float a{glm::dot(ray.direction, ray.direction)};
    float b{2.0f*(glm::dot(l,ray.direction))};
    float c{glm::dot(l,l) - radius*radius};
    
    float det = b*b-4.0f*a*c;
    if (det>=0.0f) {//wenn es min. eine Lösung gibt
        float t1((-b-sqrt(det))/(2.0f*a));
        float t2((-b+sqrt(det))/(2.0f*a));
        
        if (t1 < t2){//nimm Punkt, welcher näher dran ist
            if (t1>=0 && t1<ray.distance) {//collide if nearest point in front of camera
                ray.distance=t1;
                auto p(l-(ray.origin+ray.direction*t1));
                return std::make_pair(true, Ray(p,glm::normalize(center-p)));//use t1
            } else {
                return std::make_pair(false, Ray());//keine Lösung
            }
        } else{
            if (t2>=0 && t2<ray.distance) {//collide if nearest point in front of camera
                ray.distance=t2;
                auto p(l-(ray.origin+ray.direction*t2));
                return std::make_pair(true, Ray(p,glm::normalize(center-p)));//use t2
            } else {
                return std::make_pair(false, Ray());//keine Lösung
            }
                
        }
    } else 
        return std::make_pair(false, Ray());//keine Lösung
}