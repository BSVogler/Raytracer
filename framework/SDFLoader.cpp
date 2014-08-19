/* 
 * File:   SDFLoader.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 8. Juli 2014, 18:52
 */

#include <algorithm>
#include "SDFloader.hpp"
#include "Camera.hpp"
#include "Box.hpp"
#include "Sphere.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Material.hpp"
#include "LightPoint.hpp"

using namespace std;

SDFLoader::SDFLoader() {
}

SDFLoader::SDFLoader(const SDFLoader& orig) {
}

SDFLoader::~SDFLoader() {
}

/**
 * Loads a scene file and reacts to the commands in it
 * @param scenefile the string to the file
 * @return 
 */
Scene SDFLoader::load(std::string const& scenefile) {
    cout << "Loading file: " << scenefile << endl;
    Scene scene = Scene();
    
    std::map<std::string, Material> mMap;
    std::map<std::string, LightPoint> lMap;
    std::map<std::string, RenderObject*> roMap;
    
    string line;
    ifstream file(scenefile);
    stringstream ss;
    //file.open(scenefile, ios::in);
    if (file.is_open()) {
        while (getline (file,line)){//get line
            ss = stringstream(line);//fill the line into stringstream
            string tmpString;
            ss >> tmpString;
            //is first string define?
            if (tmpString=="define"){
                cout << "defininig: ";
                
                ss >> tmpString;
                if (tmpString=="material"){
                    cout << "a material: "<<endl;
                    //extract name
                    string name;
                    ss>>name;

                    //extract color
                    float red, green, blue;
                    ss >> red;
                    ss >> green;
                    ss >> blue;
                    Color ca(red, green, blue);
                    ss >> red;
                    ss >> green;
                    ss >> blue;
                    Color cd(red, green, blue);
                    ss >> red;
                    ss >> green;
                    ss >> blue;
                    Color cs(red, green, blue);
                    float m;
                    ss >> m;
                    Material mat(ca, cd, cs,m, name);
                    cout << "Material specs: "<<endl<<mat;
                    mMap[name]=mat;
                } else if (tmpString=="camera"){
                    string cameraname;
                    ss >> cameraname;
                    int fovX;
                    ss >> fovX;
                    scene.camera = Camera(cameraname,fovX);
                    cout << "camera: "<<cameraname<<"("<<fovX<<")"<<endl;
                } else if (tmpString=="light"){
                    string type;
                    ss>>type;
                    
                    if (type=="diffuse") {
                        string name;
                        ss >> name;

                        glm::vec3 pos;
                        ss >> pos.x;
                        ss >> pos.y;
                        ss >> pos.z;

                        float red, green, blue;
                        ss >> red;
                        ss >> green;
                        ss >> blue;
                        Color diff(red, green, blue);

                        LightPoint light = LightPoint(name, pos, diff);
                        cout << "light point: "<<name<<"("<<pos.x<<","<<pos.y<<","<<pos.z<<","<<diff<<")"<<endl;
                        lMap[name] = light;
                    }else if (type=="ambient") {
                        string lightname;
                        ss >> lightname;//name get's ignored
                        
                        float red, green, blue;
                        ss >> red;
                        ss >> green;
                        ss >> blue;
                        Color amb(red, green, blue);
                        
                        scene.amb = amb;
                        cout << "ambient light "<<amb<<endl;
                    } else {
                        cout << "type not supported yet."<<endl;
                    }
                } else if (tmpString=="shape"){
                    string classname;
                    ss >> classname;
                    cout << "Shape \""<< classname << "\"."<<endl;
                    transform(classname.begin(), classname.end(),classname.begin(), ::toupper);
                    
                    string name;
                    ss >> name;
                    
                    RenderObject* rObject = nullptr;
                    if (classname=="BOX"){
                        int edge1x, edge1y, edge1z;
                        ss>> edge1x;
                        ss>> edge1y;
                        ss>> edge1z;
                            
                        int edge2x, edge2y, edge2z;
                        ss>> edge2x;
                        ss>> edge2y;
                        ss>> edge2z;
                        
                        string materialName;
                        ss>>materialName;
                        Material material = mMap[materialName];
                        
                        rObject = new Box(
                                name,
                                glm::vec3(edge1x, edge1y, edge1z),
                                glm::vec3(edge2x, edge2y, edge2z),
                                material
                                );
                    }else if (classname=="SPHERE") {
                        int posX, posY, posZ;
                        ss>> posX;
                        ss>> posY;
                        ss>> posZ;
                        float radius;
                        ss>>radius;
                        
                        string materialString;
                        ss>>materialString;
                        
                        rObject = new Sphere(
                                name,
                                glm::vec3(posX, posY, posZ),
                                radius,
                                mMap[materialString]
                                );
                        cout << "Shape \""<< name << "\" aus Material "<<materialString<<" mit Radius: "<<radius<<"@("<<posX<<","<<posY<<","<<posZ<<")"<<endl;
                    }else cout << "ERROR: Shape \""<< classname << "\" not defined."<<endl;
                    
                    if (rObject != nullptr)
                        roMap[name] = rObject;
                } else
                    cout << "object to define not implemented:"<<ss.str() <<endl;
            } else if (tmpString=="render"){
                ss >> scene.camname;
                ss >> scene.outputFile;
                ss >> scene.resX;
                ss >> scene.resY;
                string antialiase;
                ss >> scene.antialiase;
                
                //set default if not set
                if (scene.resX<=0) scene.resX=480;
                if (scene.resY<=0) scene.resY=320;
                cout << "Scene should be rendered from "<< scene.camname << " at resolution "<<scene.resX<<"x"<< scene.resY<<"with "<< scene.antialiase<<"x SSAA to "<<scene.outputFile<<endl;
            } else if (tmpString=="#"){
                cout << line << endl;//just print comment lines
            } else
                cout << "Line not supported:"<<line <<endl;
        }
        file.close();
    }else cout << "Unable to open file"; 
    
    //save collected data in scene
    scene.materials = mMap;
    scene.renderObjects = roMap;
    scene.lights = lMap;
    return scene; 
}