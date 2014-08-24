/* 
 * File:   RenderObject.hpp
 * Author: Benedikt Vogler
 *
 * Created on 14. August 2014, 15:47
 */

#ifndef RENDEROBJECT_HPP
#define	RENDEROBJECT_HPP

#include <glm/glm.hpp>
#include "ray.hpp"
#include "Material.hpp"
#include <string>
#include "Intersection.hpp"

using std::string;

class RenderObject {
public:
    RenderObject(string const& name, Material const& material) :
        name(name), material(material)
    {}

    virtual Intersection intersect(Ray const& ray) const  =0;
    virtual void translate(glm::vec4 const& translateLocation) = 0;
    virtual void rotate(int angle, glm::vec3 const& vector) = 0;
    virtual void scale(double scale) = 0;

    Material getMaterial() const {
        return material;
    }

private:
    Material material;
    string name;
};

#endif	/* RENDEROBJECT_HPP */