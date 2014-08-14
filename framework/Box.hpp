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
        RenderObject("unnamed", Material()), edge1(glm::vec3()), edge2(glm::vec3())
    {};
    
    Box(string name, glm::vec3 const& edge1, glm::vec3 const&  edge2, Material const& material) :
        RenderObject(name, material), edge1(edge1), edge2(edge2)
    {}
    
    Box(const Box& orig);
    virtual ~Box();
private:
    glm::vec3 edge1;
    glm::vec3 edge2;

};

#endif	/* BOX_HPP */

