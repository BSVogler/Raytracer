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

class Sphere {
public:
    Sphere();
    Sphere(const Sphere& orig);
    virtual ~Sphere();
    glm::vec3 intersect(Ray const& ray) const;
private:
    glm::vec3 center;
    float radius;
};

#endif	/* SPHERE_HPP */

