#include "RenderObject.hpp"

#define GLM_FORCE_RADIANS

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

void RenderObject::translate(glm::vec3 const& transl) {
    t = glm::translate(glm::mat4(), transl) * t;
    t_inv = glm::translate(glm::mat4(), -transl) * t_inv;
}

void RenderObject::scale(const glm::vec3& axis) {
    t = glm::scale(glm::mat4(), axis) * t;
    t_inv = glm::scale(glm::mat4(), -axis) * t_inv;
}

/**
 * 
 * @param angle in radians
 * @param axis the axis to rotate around
 */
void RenderObject::rotate(float angle, const glm::vec3& axis) {
    t = glm::rotate(glm::mat4(), angle, axis) * t;
    t_inv = glm::rotate(glm::mat4(), -angle, axis) * t_inv;
}
