/* 
 * File:   Composite.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 21. August 2014, 10:51
 */

#include "Composite.hpp"

typedef std::pair<bool, Ray> Intersection;

Intersection Composite::intersect(Ray const& ray) const {
    std::vector<Intersection> intersections;

    //collect every intersection
    for(auto child = children.begin(); child != children.end(); child++) {//every render object
        intersections.push_back(child->intersect(ray));
    }
  
    //return nearest point
    return *std::min_element(
        intersections.begin(),
        intersections.end(),
        [](Intersection const& a, Intersection const& b)->bool { return a.second.distance < b.second.distance;}
    );

}