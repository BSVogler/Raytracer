/* 
 * File:   Sphere.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 4. Juli 2014, 19:25
 */

#include "Sphere.hpp"
#include "Intersection.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


void Sphere::transalte(glm::vec4 translateLocation)  {
	/*
	glm::vec4 translateLoc = glm::vec4(translateLocation, 1.0);
	glm::mat4 translateModel = glm::mat4();
	translateModel[3] = glm::vec4(center, 1.0);

	glm::vec4 newCenter = translateModel * translateLoc;

	center = glm::vec3(newCenter.x, newCenter.y, newCenter.z);
	*/

	glm::mat4 location = glm::translate(translateLocation);

}
void Sphere::rotate(int angle)  {
	
}
void Sphere::(double  scale)  {
	radius *= scale;
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