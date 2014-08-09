/* 
 * File:   LightPoint.hpp
 * Author: Benedikt Vogler
 *
 * Created on 9. August 2014, 16:25
 */

#ifndef LIGHTPOINT_HPP
#define	LIGHTPOINT_HPP

#include <string>
#include <glm/glm.hpp>
#include "color.hpp"

class LightPoint {
public:
    LightPoint();
    LightPoint(std::string const& name, glm::vec3 const& pos, Color const& diff);
    LightPoint(const LightPoint& orig);
    virtual ~LightPoint();
private:
    std::string name;
    glm::vec3 pos;
    Color diff;
};

#endif	/* LIGHTPOINT_HPP */

