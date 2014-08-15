/* 
 * File:   Box.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 14. August 2014, 16:59
 */

#include "Box.hpp"

std::pair<bool, glm::vec3> Box::intersect(const Ray& ray) const {
    return std::pair<bool, glm::vec3>(false, ray.origin);//never intersect
}

