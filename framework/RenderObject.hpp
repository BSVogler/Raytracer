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

class RenderObject {
public:
    virtual std::pair<bool, glm::vec3> intersect(Ray const& ray) const  =0 ;
private:
    glm::vec3  pos;
};

#endif	/* RENDEROBJECT_HPP */