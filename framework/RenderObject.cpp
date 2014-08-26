#include "RenderObject.hpp"


glm::mat4 const& RenderObject::worldCoords() const{
	return world_transformation;
}

void RenderObject::invertWorldCoords(glm::mat4 const& m){
	world_transformation *= m;
	world_transformation_inv = glm::inverse(world_transformation);
}