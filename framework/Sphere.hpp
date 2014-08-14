/* 
 * File:   Sphere.hpp
 * Author: Benedikt Vogler
 *
 * Created on 4. Juli 2014, 19:25
 */

#ifndef SPHERE_HPP
#define	SPHERE_HPP

#include <glm/glm.hpp>
#include "ray.hpp"
#include "RenderObject.hpp"


class Sphere: public RenderObject {
public:
    Sphere():
        RenderObject(Material()), radius(0)
    {};
    
    Sphere(glm::vec3 center, float radius) :
        RenderObject(Material()), center(center), radius(radius)
    {}

    Sphere(const Sphere& orig);
    virtual ~Sphere();
    std::pair<bool, glm::vec3> intersect(Ray const& ray) const;
    
private:
    float radius;
    glm::vec3 center;
};

#endif	/* SPHERE_HPP */

