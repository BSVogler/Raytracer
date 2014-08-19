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
    bool antialiase;
    
//    //manual destructor needed?
//    ~Scene(){
//        for (auto itr=materials.begin(); itr !=materials.end();++itr) {
//            materials.erase(itr);
//        }
//        for (auto itr=lights.begin(); itr !=lights.end();++itr) {
//            lights.erase(itr);
//        }
//        for (auto itr=renderObjects.begin(); itr !=renderObjects.end();++itr) {
//            renderObjects.erase(itr);
//        }
//    }
};


#endif	/* SCENE_HPP */

