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


class Sphere {
public:
    Sphere();
    Sphere(glm::vec3 center, float radius) :
        center(center), radius(radius)
    {}

    Sphere(const Sphere& orig);
    virtual ~Sphere();
    std::pair<bool, glm::vec3> intersect(Ray const& ray) const;
private:
    glm::vec3 center;
    float radius;
};

#endif	/* SPHERE_HPP */

