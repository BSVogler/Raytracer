/* 
 * File:   Scene.hpp
 * Author: Benedikt Vogler
 *
 * Created on 8. Juli 2014, 18:54
 */

#ifndef SCENE_HPP
#define	SCENE_HPP

#include "Material.hpp"
#include "Camera.hpp"
#include <vector>

struct Scene {
    public:
        std::vector<Material> materials;
        Camera camera;
        std::string camname;
        int resX;
        int resY;
        std::string outputFile;
    
};


#endif	/* SCENE_HPP */

