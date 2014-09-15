/* 
 * File:   SDFLoader.hpp
 * Author: Benedikt Vogler
 *
 * Created on 8. Juli 2014, 18:52
 */

#ifndef SDFLOADER_HPP
#define	SDFLOADER_HPP

#include "Scene.hpp"
#include <vector>

class SDFLoader {
public:
    static Scene load(std::string const& scenefile);
    static Material getMaterial(string name, std::vector<Material> data);
    static LightPoint getLight(string name, std::vector<LightPoint> data);
    static std::shared_ptr<RenderObject> getShape(string name, std::vector<std::shared_ptr<RenderObject>> data); 
};

#endif	/* SDFLOADER_HPP */

