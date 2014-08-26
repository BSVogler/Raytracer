/* 
 * File:   Composite.hpp
 * Author: Benedikt Vogler
 *
 * Created on 21. August 2014, 10:51
 */

#ifndef COMPOSITE_HPP
#define	COMPOSITE_HPP

#include "RenderObject.hpp"
#include <vector>


class Composite : public RenderObject {
public:
    Composite(string const& name):
        RenderObject(name,Material())
    {}
    
    void add_child(RenderObject* const& child);
    virtual Intersection intersect(const Ray& ray) const;
	
	void translate(glm::vec3 translateLocation);
	void rotate(double angle, glm::vec3 vector);
	void scale(glm::vec3 axis);

private:
    std::vector<RenderObject*> children;

};

#endif	/* COMPOSITE_HPP */

