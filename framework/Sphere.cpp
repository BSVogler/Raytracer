/* 
 * File:   Sphere.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 4. Juli 2014, 19:25
 */

#include "Sphere.hpp"
#include "Intersection.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


void Sphere::translate(glm::vec3 const& translateLocation) {
	glm::vec4 translateLoc = glm::vec4(translateLocation, 1.0);
	glm::mat4 translateModel = glm::mat4();
	translateModel[3] = glm::vec4(center, 1.0);

	glm::vec4 newCenter = translateModel * translateLoc;

	center = glm::vec3(newCenter.x, newCenter.y, newCenter.z);
	


}

void Sphere::rotate(double angle, glm::vec3 const& vector) {
	glm::mat4 rotateModel = glm::mat4();
	rotateModel[2] = glm::vec4(0, glm::cos(angle), glm::sin(angle), 0);
	rotateModel[3] = glm::vec4(0, -1 * glm::sin(angle), glm::cos(angle), 0);
	
	glm::vec4 rotateLoc = glm::vec4(vector, 1);
	glm::vec4 newCenter = rotateModel * rotateLoc;
	center = glm::vec3(newCenter.x, newCenter.y, newCenter.z);
}

void Sphere::scale(glm::vec3 const& axis){
	glm::mat4 scaleModel = glm::mat4();
	scaleModel[0] = glm::vec4(axis.x, 0, 0, 0);
	scaleModel[1] = glm::vec4(0, axis.y, 0, 0);
	scaleModel[2] = glm::vec4(0, 0, axis.z, 0);
	scaleModel[3] = glm::vec4(0, 0, 0, 1);

	glm::vec4 scaleLoc = glm::vec4(center, 1);
	glm::vec4 newCenter = scaleModel * scaleLoc;
	center = glm::vec3(newCenter.x, newCenter.y, newCenter.z);
}

Intersection Sphere::intersect(Ray const& ray) const {
    glm::vec3 CO{ ray.origin - center };//why CO and not OC???
    float a{ glm::dot(ray.direction, ray.direction) };
    float b{ 2.0f * glm::dot(CO, ray.direction) };
    float c{ glm::dot(CO,CO) - radius*radius};
    
    float det = b*b - 4.0f*a*c;
    if (det >= 0.0f) {//wenn es min. eine Lösung gibt
        float sqrtdet(sqrt(det));
        float t1((-b - sqrtdet) / (2.0f*a));
        float t2((-b + sqrtdet) / (2.0f*a));
        
        if (t2 < t1)//nimm Punkt, welcher näher dran ist
            std::swap(t2,t1);
        
        if (t1>=0) {//collide if nearest point in front of camera
            Intersection inter;
            inter.hit = true;
            inter.ray.origin = ray.origin+ray.direction*t1;
            inter.ray.direction = glm::normalize(inter.ray.origin-center);//use t1, normal is n=CI=I-C, same as CO+i
            inter.distance= t1;
            inter.material = getMaterial();
            return inter;
        }
    }
    return Intersection();//keine Lösung
}