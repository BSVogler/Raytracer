/* 
 * File:   Camera.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 9. August 2014, 14:49
 */

#include "Camera.hpp"

Camera::Camera():
    name("unnamed"),
    fovX(100)
{}

Camera::Camera(const std::string name, const int fovX):
    name(name),
    fovX(fovX)
{}