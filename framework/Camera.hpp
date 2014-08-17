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
    int GetFovX() const {
        return fovX;
    }

    glm::vec3 GetN() const {
        return n;
    }

    glm::vec3 GetOrigin() const {
        return origin;
    }

    glm::vec3 GetUp() const {
        return up;
    }

private:
    std::string name;
    int fovX;
    glm::vec3 origin;
    glm::vec3 n;
    glm::vec3 up;
};

#endif	/* CAMERA_HPP */

