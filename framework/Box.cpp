/* 
 * File:   Box.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 14. August 2014, 16:59
 */

#include "Box.hpp"
#include "Intersection.hpp"

Intersection Box::intersect(Ray const& ray) const {
    Intersection inter;
    
    //calculate smallest hit t's
    float minX = ( pmin.x - ray.origin.x ) / ray.direction.x;
    float maxX = ( pmax.x - ray.origin.x ) / ray.direction.x;
    if (minX > maxX) std::swap(minX, maxX);
    
    float tminy = ( pmin.y - ray.origin.y ) / ray.direction.y;
    float maxY = ( pmax.y - ray.origin.y ) / ray.direction.y;
    if (tminy > maxY) std::swap(tminy, maxY);
   
    //XY
    //fitler ray not hitting, maybe useless chcek
    if ((minX > maxY) || (tminy > maxX))
        return Intersection(); 
    
    //find bigger/smaller values
    if (tminy > minX)
        minX = tminy;
    if (maxY < maxX)
        maxX = maxY;

    //z
    float minZ = ( pmin.z - ray.origin.z ) / ray.direction.z;
    float maxZ = ( pmax.z - ray.origin.z ) / ray.direction.z;
    if (minZ > maxZ) std::swap(minZ, maxZ);
    //ray not hitting
    if ((minX > maxZ) || (minZ > maxX))
        return Intersection(); 
    
    if (minZ > minX)
        minX = minZ;
    if (maxZ < maxX)
        maxX = maxZ;
    
    
    float t=minX;
    if (t<=0)
        return Intersection();  
    
    auto p = ray.origin + t * ray.direction;
    inter.ray.origin = p;
    
    if(fabs(p.x - pmin.x) < 0.0001f){//normal from left
        inter.ray.direction = glm::vec3 (-1.0f, 0.0f, 0.0f);
    }else if(fabs(p.x - pmax.x) < 0.0001f){//normal from right
        inter.ray.direction = glm::vec3 (1.0f, 0.0f, 0.0f);
    }else if(fabs(p.y - pmin.y) < 0.0001f){//normal from bottom
        inter.ray.direction = glm::vec3 (0.0f, -1.0f, 0.0f);
    }else if(fabs(p.y - pmax.y) < 0.0001f){//normal from up
        inter.ray.direction = glm::vec3 (0.0f, 1.0f, 0.0f);
    }else if(fabs(p.z - pmin.z) < 0.0001f){//normal from front
        inter.ray.direction = glm::vec3 (0.0f, 0.0f, -1.0f);//somehow the normal is in the wrong way?
    }else if(fabs(p.z - pmax.z) < 0.0001f){//normal from back
        inter.ray.direction = glm::vec3 (0.0f, 0.0f, 1.0f);//somehow the normal is in the wrong way?
    }
    
    inter.distance = t;
    inter.material = getMaterial();
    inter.hit=true;
    return inter;    
        

}





