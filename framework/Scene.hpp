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

struct Scene {
    std::map<std::string, Material> materials;
    std::map<std::string, LightPoint> lights;
    std::map<std::string, RenderObject*> renderObjects;
    Camera camera;
    std::string camname;
    int resX;
    int resY;
    std::string outputFile;
    Color amb;
};


#endif	/* SCENE_HPP */

