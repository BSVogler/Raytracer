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

    virtual Intersection intersect(Ray const& ray) const =0;
	

    Material getMaterial() const {
        return material;
    }


    glm::mat4 const& worldCoords() const;

    void setWorld_transformation(glm::mat4 world_transformation) {
        this->world_transformation = world_transformation;
    }

    void invertWorldCoords(glm::mat4 const& m);
    virtual void scale(glm::vec3 const& axis) =0;
    virtual void translate(glm::vec3 const& axis) =0;
    virtual void rotate(double angle, glm::vec3 const& axis)=0;

private:
    Material material;
    string name;
    glm::mat4 world_transformation;
    glm::mat4 world_transformation_inv;

};

#endif	/* RENDEROBJECT_HPP */