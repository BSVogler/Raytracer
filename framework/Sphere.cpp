/* 
 * File:   Sphere.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 4. Juli 2014, 19:25
 */

#include "Sphere.hpp"

Sphere::Sphere() {
}

Sphere::Sphere(const Sphere& orig) {
}

Sphere::~Sphere() {
}

glm::vec3 Sphere::intersect(Ray const& ray) const {
    float b = 2 *(glm::dot(ray.origin,ray.direction));
    float c = glm::dot(ray.origin,ray.origin) - radius*radius;
    
    int root = b*b-4*c;
    if (root>0) {//wenn es min. eine Lösung gibt
        float t1 = -b-sqrt(root);
        float t2 = -b+sqrt(root);
        
        if (t1 < t2)//nimm Punkt, welcher näher dran ist
            return ray.origin+ray.direction*t1;//use t1
        else 
            return ray.origin+ray.direction*t2;//use t2
    } else 
        return ray.origin;//keine Lösung
}




