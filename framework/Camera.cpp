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

Camera::Camera():
    name("unnamed"),
    fovX(100),
    transformation(glm::mat4x4()),
    transformation_inv(glm::mat4x4())
{}

Camera::Camera(std::string const& name, const int fovX):
    name(name),
    fovX(fovX),
    transformation(glm::mat4x4()),
    transformation_inv(glm::mat4x4())
{}

void Camera::translate(glm::vec3 const& transl) {
  auto m = glm::translate(glm::mat4(), transl);
  transformation = m * transformation;
  transformation_inv = transformation_inv * m;
}

void Camera::rotate(float angle, glm::vec3 const& axis) {
  auto m = glm::rotate(glm::mat4(), angle, axis);
  transformation = m * transformation;
  transformation_inv = transformation_inv * m;
}