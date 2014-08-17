#ifndef BUW_RAY_HPP
#define BUW_RAY_HPP

#include <glm/glm.hpp>

/**
 * A reay consists of an origin and a diretion.
 */
struct Ray
{
    glm::vec3 origin;
    glm::vec3 direction;
};

#endif