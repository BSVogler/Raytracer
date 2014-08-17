/* 
 * File:   Camera.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 9. August 2014, 14:49
 */

#include "Camera.hpp"
#include "glm/detail/type_vec.hpp"

Camera::Camera():
    name("unnamed"),
    fovX(100),
    origin(glm::vec3(0,0,0)),  
    n(glm::vec3(0,0,-1)),
    up(glm::vec3(0,1,0))
{}

Camera::Camera(const std::string name, const int fovX):
    name(name),
    fovX(fovX),
    origin(glm::vec3(0,0,0)),  
    n(glm::vec3(0,0,-1)),
    up(glm::vec3(0,1,0))
{}