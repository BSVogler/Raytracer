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

void Composite::transalte(glm::vec3 const& translateLocation) const {
	for (auto child = children.begin(); child != children.end(); ++child) {//every children
		(*child)->transalte(translateLocation);
	}
}
void Composite::rotate(int const& angle) const {
	for (auto child = children.begin(); child != children.end(); ++child) {//every children
		(*child)->rotate(angle);
	}
}
void Composite::scale(double const& scale) const {
	for (auto child = children.begin(); child != children.end(); ++child) {//every children
		(*child)->scale(scale);
	}
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