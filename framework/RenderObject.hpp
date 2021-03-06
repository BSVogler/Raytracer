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
        name(name), material(material), transformed(false)
    {}

    virtual Intersection intersect(Ray const& ray) const =0;
	

    Material const& getMaterial() const {
        return material;
    }

    glm::mat4 const& getWorldTransf() const{
        return t;
    }

    glm::mat4 const& getWorldTransfInv() const {
        return t_inv;
    }
    
    glm::mat3 const& getWorldTransfInvTransp() const {
        return t_inv_transp;
    }
    
    bool isTransformed() const {
        return transformed;
    }
    
    string getName() const {
        return name;
    }
    
    void scale(glm::vec3 const& axis);
    void translate(glm::vec3 const& axis);
    void rotate(float angle, glm::vec3 const& axis);

private:
    Material material;
    string name;
    glm::mat4 t;
    glm::mat4 t_inv;
    glm::mat3 t_inv_transp;
    bool transformed;
};

#endif	/* RENDEROBJECT_HPP */