#ifndef BUW_RAY_HPP
#define BUW_RAY_HPP

#include <glm/glm.hpp>
#include <ostream>

/**
 * A reay consists of an origin and a diretion.
 */
struct Ray
{
    glm::vec3 origin;
    glm::vec3 direction;
    float mint;
    float maxt;
    
    Ray(glm::vec3 origin=glm::vec3(), glm::vec3 direction=glm::vec3()) :
        origin(origin), direction(direction), mint(0.000001f), maxt(INFINITY)
    {}

    
    friend std::ostream& operator<<(std::ostream& os, Ray const& r){
        return os<<"("<<r.origin.x<<","<<r.origin.y<<","<<r.origin.z<<")+("<<r.direction.x<<","<<r.direction.y<<","<<r.direction.z<<")";
    }
    
};

#endif