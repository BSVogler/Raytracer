/* 
 * File:   Box.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 14. August 2014, 16:59
 */

#include "Box.hpp"
#include "Intersection.hpp"

Intersection Box::intersect(Ray const& ray) const {
    Ray ray_t;
    if (isTransformed())
        ray_t = Ray(
            glm::vec3(getWorldTransfInv() * glm::vec4(ray.origin, 1)),
            glm::vec3(getWorldTransfInv() * glm::vec4(ray.direction, 0))
        );
    else
        ray_t = ray;
    
    Intersection inter;
    
    //calculate smallest hit t's
    float minX = ( pmin.x - ray_t.origin.x ) / ray_t.direction.x;
    float maxX = ( pmax.x - ray_t.origin.x ) / ray_t.direction.x;
    if (minX > maxX) std::swap(minX, maxX);
    
    float tminy = ( pmin.y - ray_t.origin.y ) / ray_t.direction.y;
    float maxY = ( pmax.y - ray_t.origin.y ) / ray_t.direction.y;
    if (tminy > maxY) std::swap(tminy, maxY);
   
    //XY
    //fitler ray_t not hitting, maybe useless chcek
    if ((minX > maxY) || (tminy > maxX))
        return Intersection(); 
    
    //find bigger/smaller values
    if (tminy > minX)
        minX = tminy;
    if (maxY < maxX)
        maxX = maxY;

    //z
    float minZ = ( pmin.z - ray_t.origin.z ) / ray_t.direction.z;
    float maxZ = ( pmax.z - ray_t.origin.z ) / ray_t.direction.z;
    if (minZ > maxZ) std::swap(minZ, maxZ);
    //ray_t not hitting
    if ((minX > maxZ) || (minZ > maxX))
        return Intersection(); 
    
    if (minZ > minX)
        minX = minZ;
    if (maxZ < maxX)
        maxX = maxZ;
    
    
    float t=minX;
    if (t<ray_t.mint ||t>ray_t.maxt)
        return Intersection();  
    
    auto p = ray_t.origin + t * ray_t.direction;
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
    if (isTransformed()) inter.ray.direction = getWorldTransfInvTransp()*inter.ray.direction;
    inter.distance = t;
    inter.material = getMaterial();
    inter.hit=true;
    return inter;    
        

}





