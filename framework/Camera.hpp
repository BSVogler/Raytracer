/* 
 * File:   Camera.hpp
 * Author: Benedikt Vogler
 *
 * Created on 9. August 2014, 14:49
 */

#ifndef CAMERA_HPP
#define	CAMERA_HPP

#include <string>

class Camera {
public:
    Camera();
    Camera(std::string const name, int const fovX);
private:
    std::string name;
    int fovX;
};

#endif	/* CAMERA_HPP */

