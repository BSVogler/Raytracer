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
    
    float tmin = (edge1.x - ray.origin.x) / ray.direction.x;
    float tmax = (edge2.x - ray.origin.x) / ray.direction.x;
    if(tmin > tmax) std::swap(tmin, tmax);

    float ty_min = (edge1.y - ray.origin.y) / ray.direction.y;
    float ty_max = (edge2.y - ray.origin.y) / ray.direction.y;
    if(ty_min > ty_max) std::swap(ty_min, ty_max);

    if((tmin > ty_max) || (ty_min > tmax)){
        inter.hit=false;
        return inter;
    }
    if(ty_min > tmin) tmin = ty_min;
    if(ty_max < tmax) tmax = ty_max;

    float tz_min = (edge1.z - ray.origin.z) / ray.direction.z;
    float tz_max = (edge2.z - ray.origin.z) / ray.direction.z;
    if(tz_min > tz_max) std::swap(tz_min, tz_max);

    if((tmin > tz_max) || (tz_min > tmax)){
        inter.hit=false;
        return inter;
    }
    if(tz_min > tmin) tmin = tz_min;
    if(tz_max < tmax) tmax = tz_max;


    glm::vec3 n = ray.origin + tmin * ray.direction;
    inter.hit = true;
    inter.ray.origin = ray.origin + tmin * ray.direction;
    inter.ray.direction = calcNormal(n.x, n.y, n.z);
    inter.distance = tmin;
    inter.material = getMaterial();
    return inter;
}

glm::vec3 Box::calcNormal(float const& x, float const& y, float const& z) const {
    glm::vec3 normal;
    if(fabs(x - edge1.x) < 0.01f){//normal from left
      normal.x = -1;
      normal.y = 0;
      normal.z = 0;
    }else if(fabs(x - edge2.x) < 0.01f){//normal from right
      normal.x = 1;
      normal.y = 0;
      normal.z = 0;
    }else if(fabs(y - edge1.y) < 0.01f){//normal from bottom
      normal.x = 0;
      normal.y = -1;
      normal.z = 0;
    }else if(fabs(y - edge2.y) < 0.01f){//normal from up
      normal.x = 0;
      normal.y = 1;
      normal.z = 0;
    }else if(fabs(z - edge1.z) < 0.01f){//normal from back
      normal.x = 0;
      normal.y = 0;
      normal.z = 1;
    }else if(fabs(z - edge2.z) < 0.01f){//normal from front
      normal.x = 0;
      normal.y = 0;
      normal.z = -1;
    }
    return normal;
}

void Box::rotate(double angle, glm::vec3 const& vector) 
{
	glm::mat4 rotateModel = glm::mat4();
	rotateModel[1] = glm::vec4(0, glm::cos(angle), glm::sin(angle), 0);
	rotateModel[2] = glm::vec4(0, -1 * glm::sin(angle), glm::cos(angle), 0);

	glm::vec4 rotateLocEdge1 = glm::vec4(edge1, 1);
	glm::vec4 newEdge1 = rotateModel * rotateLocEdge1;
	edge1 = glm::vec3(newEdge1.x, newEdge1.y, newEdge1.z);


	glm::vec4 rotateLocEdge2 = glm::vec4(edge2, 1);
	glm::vec4 newEdge2 = rotateModel * rotateLocEdge2;
	edge2 = glm::vec3(newEdge2.x, newEdge2.y, newEdge2.z);
}

void Box::scale(glm::vec3 const& axis) 
{
	glm::mat4 scaleModel = glm::mat4();
	scaleModel[0] = glm::vec4(axis.x,0 , 0, 0);
	scaleModel[1] = glm::vec4(0,  axis.y, 0, 0);
	scaleModel[2] = glm::vec4(0, 0, axis.z, 0);
	scaleModel[3] = glm::vec4(0, 0, 0, 1);

	glm::vec4 scaleLocEdge1 = glm::vec4(edge1, 1);
	glm::vec4 newEdge1 = scaleModel * scaleLocEdge1;
	edge1 = glm::vec3(newEdge1.x, newEdge1.y, newEdge1.z);

	glm::vec4 scaleLocEdge2 = glm::vec4(edge2, 1);
	glm::vec4 newEdge2 = scaleModel * scaleLocEdge2;
	edge2 = glm::vec3(newEdge2.x, newEdge2.y, newEdge2.z);
}

void Box::translate(glm::vec3 const& translateLocation) {
	glm::vec4 translateLoc = glm::vec4(translateLocation,1.0);
	glm::mat4 translateModelEdge1 = glm::mat4();
	translateModelEdge1[3] = glm::vec4(edge1, 1.0);

	glm::vec4 newEdge1 = translateModelEdge1 * translateLoc;

	edge1 = glm::vec3(newEdge1.x, newEdge1.y, newEdge1.z);

	glm::mat4 translateModelEdge2 = glm::mat4();
	translateModelEdge2[3] = glm::vec4(edge2, 1.0);

	glm::vec4 newEdge2 = translateModelEdge2 * translateLoc;

	edge2 = glm::vec3(newEdge2.x, newEdge2.y, newEdge2.z);
}


