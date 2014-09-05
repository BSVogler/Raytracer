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
    );
    
    Intersection intersect(Ray const& ray) const override;

private:
    glm::vec3 pmin;
    glm::vec3 pmax;
    glm::vec3 calcNormal(float const& x, float const& y, float const& z) const;
};

#endif	/* BOX_HPP */

