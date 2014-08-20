/* 
 * File:   Sphere.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 4. Juli 2014, 19:25
 */

#include "Sphere.hpp"
#include <glm/glm.hpp>

std::pair<bool, Ray> Sphere::intersect(Ray const& ray) const {
    glm::vec3 p{center};
    float a{glm::dot(ray.direction, ray.direction)};
    float b{2.0f*(glm::dot(p,ray.direction))};
    float c{glm::dot(p,p) - radius*radius};
    
    float det = b*b-4.0f*a*c;
    if (det>=0.0f) {//wenn es min. eine Lösung gibt
        float t1((-b-sqrt(det))/(2.0f*a));
        float t2((-b+sqrt(det))/(2.0f*a));
        
        if (t1 < t2){//nimm Punkt, welcher näher dran ist
            if (t1>=0 && t1<ray.distance) {//collide if nearest point in front of camera
                ray.distance=t1;
                auto i(ray.direction*t1);
                return std::make_pair(true, Ray(i,glm::normalize(i-center)));//use t1, normal is n=CI=I-C
            } else {
                return std::make_pair(false, Ray());//keine Lösung
            }
        } else{
            if (t2>=0 && t2<ray.distance) {//collide if nearest point in front of camera
                ray.distance=t2;
                auto i(ray.direction*t2);
                return std::make_pair(true, Ray(i,glm::normalize(i-center)));//use t2, normal is n=CI=I-C
            } else {
                return std::make_pair(false, Ray());//keine Lösung
            }
                
        }
    } else 
        return std::make_pair(false, Ray());//keine Lösung
}