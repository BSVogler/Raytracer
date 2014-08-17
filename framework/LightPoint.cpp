/* 
 * File:   LightPoint.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 9. August 2014, 16:25
 */

#include "LightPoint.hpp"
#include "glm/detail/type_vec.hpp"

LightPoint::LightPoint() :
    name("unnamed"),
    pos(glm::vec3(0,0,0)),
    diff(Color())   
{}

LightPoint::LightPoint(const std::string& name, const glm::vec3& pos, const Color& diff):
    name(name),
    pos(pos),
    diff(diff)   
{}