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

using std::string;

class RenderObject {
public:
    RenderObject(string const& name, Material const& material) :
        name(name), material(material)
    {}

    virtual std::pair<bool, glm::vec3> intersect(Ray const& ray) const  =0;
    Material getMaterial() const {
        return material;
    }

private:
    Material material;
    string name;
};

#endif	/* RENDEROBJECT_HPP */