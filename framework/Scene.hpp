/* 
 * File:   Scene.hpp
 * Author: Benedikt Vogler
 *
 * Created on 8. Juli 2014, 18:54
 */

#ifndef SCENE_HPP
#define	SCENE_HPP

#include "Material.hpp"
#include <vector>

struct Scene {
    std::vector<Material> materials;
    
    Scene(std::vector<Material> materials) :
        materials(materials)
    {}

};


#endif	/* SCENE_HPP */

