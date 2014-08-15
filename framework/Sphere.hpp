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
        RenderObject("unnamed", Material()), radius(0)
    {};
    
    /**
     * Creates a shpere.
     * @param name The name of the shpere.
     * @param center the center position vector of the sphere
     * @param radius The radius of the sphere.
     * @param material 
     */
    Sphere(string name, glm::vec3 const& center, float const radius, Material const& material) :
        RenderObject(name, material), center(center), radius(radius)
    {}

    Sphere(const Sphere& orig);
    virtual ~Sphere();
    std::pair<bool, glm::vec3> intersect(Ray const& ray) const;
    
private:
    float radius;
    glm::vec3 center;
};

#endif	/* SPHERE_HPP */

