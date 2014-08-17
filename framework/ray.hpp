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
    
    friend std::ostream& operator<<(std::ostream& os, Ray const& r){
        return os<<"("<<r.origin.x<<","<<r.origin.y<<","<<r.origin.z<<")+("<<r.direction.x<<","<<r.direction.y<<","<<r.direction.z<<")";
    }
    
};

#endif