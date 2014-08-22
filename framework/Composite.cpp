/* 
 * File:   Composite.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 21. August 2014, 10:51
 */

#include "Composite.hpp"
#include "Intersection.hpp"
#include <algorithm>

void Composite::add_child(RenderObject* const& child) {
    children.push_back(child);
}

Intersection Composite::intersect(Ray const& ray) const {
    std::vector<Intersection> intersections;

    //collect every intersection
    for(auto child = children.begin(); child != children.end(); ++child) {//every children
        auto intersection = (*child)->intersect(ray);
        if (intersection.hit)
            intersections.push_back(intersection);
    }
  
    if (intersections.size()==0) return Intersection();//no intersection
    
    //return only intersection with nearest point
    return *std::min_element(
        intersections.begin(),
        intersections.end(),
        [](Intersection const& a, Intersection const& b)->bool { return a.distance < b.distance;}
    );

}