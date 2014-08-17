/* 
 * File:   Box.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 14. August 2014, 16:59
 */

#include "Box.hpp"

std::pair<bool, Ray> Box::intersect(const Ray& ray) const {
    return std::make_pair(false, Ray());//never intersect
}

