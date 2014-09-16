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
    
    Intersection intersect(Ray const& ray) const override;
    void add_child(std::shared_ptr<RenderObject> const& child);
	
private:
    std::vector<std::shared_ptr<RenderObject>> children;

};

#endif	/* COMPOSITE_HPP */

