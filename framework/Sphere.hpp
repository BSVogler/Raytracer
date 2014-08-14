/* 
 * File:   Sphere.hpp
 * Author: Benedikt Vogler
 *
 * Created on 4. Juli 2014, 19:25
 */

#ifndef SPHERE_HPP
#define	SPHERE_HPP

#include <glm/glm.hpp>
#include <utility>
#include "ray.hpp"
#include "RenderObject.hpp"


class Sphere: public RenderObject {
public:
    Sphere():
        RenderObject(Material(),glm::vec3()), radius(0)
    {};
    
    Sphere(glm::vec3 center, float radius) :
        RenderObject(Material(),center), radius(radius)
    {}

    Sphere(const Sphere& orig);
    virtual ~Sphere();
    std::pair<bool, glm::vec3> intersect(Ray const& ray) const;
private:
    float radius;
};

#endif	/* SPHERE_HPP */

