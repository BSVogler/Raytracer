/* 
 * File:   Composite.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 21. August 2014, 10:51
 */

#include "Composite.hpp"
#include "Intersection.hpp"
#include <algorithm>
#include <memory>

void Composite::add_child(std::shared_ptr<RenderObject> const& child) {
    children.push_back(child);
}


Intersection Composite::intersect(Ray const& ray) const {
    Ray ray_t;
    if (isTransformed())
        ray_t = Ray(
            glm::vec3(getWorldTransfInv() * glm::vec4(ray.origin, 1)),
            glm::vec3(getWorldTransfInv() * glm::vec4(ray.direction, 0))
        );
    else
        ray_t = ray;
           
    
    std::vector<Intersection> intersections;
    
    //collect every intersection
    for(auto& child : children) {//every children
        auto intersection = child->intersect(ray_t);
        if (intersection.hit && ray.mint<intersection.distance && ray.maxt>intersection.distance)
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