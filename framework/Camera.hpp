/* 
 * File:   Camera.hpp
 * Author: Benedikt Vogler
 *
 * Created on 9. August 2014, 14:49
 */

#ifndef CAMERA_HPP
#define	CAMERA_HPP

#include <string>
#include <glm/glm.hpp>

class Camera {
public:
    Camera();
    Camera(std::string const name, int const fovX);
    int GetFovX() const {
        return fovX;
    }

    glm::mat4 GetTransformation() const {
        return transformation;
    }

private:
    std::string name;
    int fovX;
    glm::mat4 transformation;
};

#endif	/* CAMERA_HPP */

