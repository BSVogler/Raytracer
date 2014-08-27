/* 
 * File:   Box.hpp
 * Author: Benedikt Vogler
 *
 * Created on 14. August 2014, 16:59
 */

#ifndef BOX_HPP
#define	BOX_HPP

#include "Material.hpp"
#include "RenderObject.hpp"
#include <glm/glm.hpp>

class Box : public RenderObject {
public:
    Box():
        RenderObject("unnamed", Material()), pmin(glm::vec3()), pmax(glm::vec3())
    {};
    
    Box(
        string name,
        glm::vec3 const& edge1,
        glm::vec3 const& edge2,
        Material const& material
    ) :
        RenderObject(name, material), pmin(edge1), pmax(edge2)
    {
        if (pmin.x>pmax.x)
            std::swap(pmin.x,pmax.x);
        if (pmin.y>pmax.y)
            std::swap(pmin.y,pmax.y);
        if (pmin.z>pmax.z)
            std::swap(pmin.z,pmax.z);
    }
    
    Box(const Box& orig);
    Intersection intersect(Ray const& ray) const;

private:
    glm::vec3 pmin;
    glm::vec3 pmax;
    glm::vec3 calcNormal(float const& x, float const& y, float const& z) const;

};

#endif	/* BOX_HPP */

