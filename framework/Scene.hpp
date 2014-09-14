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
#include "LightPoint.hpp"
#include "RenderObject.hpp"
#include <map>
#include <memory>
#include <vector>

struct Scene {
    std::vector<Material> materials;
    std::vector<LightPoint> lights;
    std::map<std::string, std::shared_ptr<RenderObject>> renderObjects;
    Camera camera;
    std::string camname;
    unsigned int resX;
    unsigned int resY;
    std::string outputFile;
    Color amb;
    unsigned antialiase;
    bool random;
};


#endif	/* SCENE_HPP */

