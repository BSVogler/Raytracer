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
    transformation(glm::mat4x4())
{}

Camera::Camera(const std::string name, const int fovX):
    name(name),
    fovX(fovX),
    transformation(glm::mat4x4())
{}