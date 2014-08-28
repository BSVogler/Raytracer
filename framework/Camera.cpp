/* 
 * File:   Camera.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 9. August 2014, 14:49
 */

#include "Camera.hpp"
#define GLM_FORCE_RADIANS
#include "glm/detail/type_vec.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

Camera::Camera():
    name("unnamed"),
    fovX(100),
    transformation(glm::mat4()),
    transformation_inv(glm::mat4())
{}

Camera::Camera(std::string const& name, const int fovX):
    name(name),
    fovX(fovX),
    transformation(glm::mat4()),
    transformation_inv(glm::mat4())
{}

void Camera::translate(glm::vec3 const& transl) {
    transformation = glm::translate(glm::mat4(), transl)*transformation;
    transformation_inv = glm::translate(glm::mat4(), -transl)*transformation_inv;
}

void Camera::rotate(float angle, glm::vec3 const& axis) {
   transformation = glm::rotate(glm::mat4(), angle, axis) * transformation;
   transformation_inv = glm::rotate(glm::mat4(), -angle, axis) * transformation_inv;
}