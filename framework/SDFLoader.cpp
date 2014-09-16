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
#include "Composite.hpp"

using namespace std;

/**
 * Loads a scene file and reacts to the commands in it
 * @param scenefile the string to the file
 * @return 
 */
Scene SDFLoader::load(std::string const& scenefile) {
    cout << "Loading file: " << scenefile << endl;
    Scene scene = Scene();
    
    scene.materials = std::vector<Material>();
    scene.lights = std::vector<LightPoint>();
    scene.renderObjects = std::vector<shared_ptr<RenderObject>>();
    
    string line;
    ifstream file(scenefile);
    //file.open(scenefile, ios::in);
    if (file.is_open()) {
        while (getline (file,line)){//get line
            stringstream ss = stringstream(line);//fill the line into stringstream
            string firstWord;
            ss >> firstWord;
            //is first string define?
            if (firstWord=="define"){
                cout << "defininig: ";
                
                ss >> firstWord;
                if (firstWord=="material"){
                    cout << "a material: "<<endl;
                    //extract name
                    string name;
                    ss>>name;

                    //extract color
                    Color ca{}, cd{}, cs{};
                    ss >> ca;
                    ss >> cd;
                    ss >> cs;
                    float m;
                    ss >> m;
                    float opacity(0);
                    ss >> opacity;
                    float refr(0);
                    ss >> refr;
                    Material mat(ca, cd, cs,m,opacity,refr, name);
                    cout << "Material specs: "<<endl<<mat;
                    scene.materials.push_back(mat);
                } else if (firstWord=="camera"){
                    string cameraname;
                    ss >> cameraname;
                    float fovX;
                    ss >> fovX;
                    scene.camera = Camera(cameraname,fovX);
                    cout << "camera: "<<cameraname<<"("<<fovX<<")"<<endl;
                    
                    if (!ss.eof()){
                        glm::vec3 pos;
                        ss >> pos.x;
                        ss >> pos.y;
                        ss >> pos.z;
                        scene.camera.translate(pos);
                        
                        //direction
                        if (!ss.eof()){
                            glm::vec3 dir;
                            ss >> dir.x;
                            ss >> dir.y;
                            ss >> dir.z;
                            auto regularDir = glm::vec3(0.0f,0.0f,-1.0f);
                            //angle between 0,0,-1 and dir
                            float angleXY =glm::dot(regularDir,dir)/(glm::length(regularDir)*glm::length(dir));
                            //rotate around y and x
                            scene.camera.rotate(angleXY,glm::vec3(1,1,0));
                            
                            //up vector
                            if (!ss.eof()){
                                glm::vec3 up;
                                ss >> up.x;
                                ss >> up.y;
                                ss >> up.z;
                                auto regularUp = glm::vec3(0.0f,1.0f,0.0f);
                                //angle between 0,1,0 and up
                                float angleZ =glm::dot(regularUp,up)/(glm::length(regularUp)*glm::length(up));
                                //rotate around z
                                scene.camera.rotate(angleZ,glm::vec3(0,0,1));
                            }
                        }
                    }
                } else if (firstWord=="light"){
                    string type;
                    ss>>type;
                    
                    if (type=="diffuse") {
                        string name;
                        ss >> name;

                        glm::vec3 pos;
                        ss >> pos.x;
                        ss >> pos.y;
                        ss >> pos.z;

                        Color diff{};
                        ss >> diff;

                        LightPoint light = LightPoint(name, pos, diff);
                        cout << "light point: "<<name<<"("<<pos.x<<","<<pos.y<<","<<pos.z<<","<<diff<<")"<<endl;
                        scene.lights.push_back(light);
                    }else if (type=="ambient") {
                        string lightname;
                        ss >> lightname;//name get's ignored
                        
                        Color amb{};
                        ss >> amb;
                        
                        scene.amb = amb;
                        cout << "ambient light "<<amb<<endl;
                    } else {
                        cout << "type not supported yet."<<endl;
                    }
                } else if (firstWord=="shape"){
                    string classname;
                    ss >> classname;
                    transform(classname.begin(), classname.end(),classname.begin(), ::toupper);
                    
                    string name;
                    ss >> name;
                    
                    shared_ptr<RenderObject> rObject;
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
                        rObject = make_shared<Box>( 
                            name,
                            glm::vec3(edge1x, edge1y, edge1z),
                            glm::vec3(edge2x, edge2y, edge2z),
                            getMaterial(materialName, scene.materials)
                        );
                    } else if (classname=="SPHERE") {
                        int posX, posY, posZ;
                        ss>> posX;
                        ss>> posY;
                        ss>> posZ;
                        float radius;
                        ss>>radius;
                        
                        string materialString;
                        ss>>materialString;
                        
                        rObject = make_shared<Sphere>( 
                            name,
                            glm::vec3(posX, posY, posZ),
                            radius,
                            getMaterial(materialString, scene.materials)
                        );
                        cout << "Sphere \""<< name << "\" aus Material "<<materialString<<" mit Radius: "<<radius<<"@("<<posX<<","<<posY<<","<<posZ<<")"<<endl;
                    } else if(classname=="COMPOSITE") {
                       rObject = make_shared<Composite>( Composite(name));
                        cout << "Composite \""<< name << "\" (" ;
                        string objectString;
                        while (!ss.eof()){
                            ss>>objectString;
                            auto linkedObject = getShape(objectString,scene.renderObjects);
                            if (linkedObject){
                                std::dynamic_pointer_cast<Composite>(rObject)->add_child(linkedObject);
                                cout<<", "<<objectString;
                            } else {
                                cout << "Error: "<<objectString <<" not found!";
                            }
                        }
                        cout<<")"<<endl;
                    } else cout << "ERROR: Shape \""<< classname << "\" not defined."<<endl;
                    
                    if (rObject)
                        scene.renderObjects.push_back(rObject);
                } else
                    cout << "object to define not implemented:"<<ss.str() <<endl;
            } else if (firstWord=="render"){
                ss >> scene.camname;
                ss >> scene.outputFile;
                ss >> scene.resX;
                ss >> scene.resY;
                ss >> scene.antialiase;
                string random;
                ss>>random;
                if (random.length()>0)
                    scene.random = (random=="random");
                
                //set default if not set
                if (scene.resX<=0) scene.resX=480;
                if (scene.resY<=0) scene.resY=320;
                cout << "Scene should be rendered from "<< scene.camname << " at resolution "<<scene.resX<<"x"<< scene.resY<<"with "<< scene.antialiase<<"x SSAA to "<<scene.outputFile<<endl;
            } else if (firstWord=="#" || firstWord.substr(0,1)=="#"){
                cout << line << endl;//just print comment lines

            } else if (firstWord == "transform"){
                string name, transform;
                float x, y, z;

                ss >> name;
                ss >> transform;
                
                cout << transform<<": " << name << ""<<endl;

                auto object = getShape(name, scene.renderObjects);
                if (object == nullptr){//check if object can be found
                    cout << "Error: " << name << " not found!"<<endl;
                } else {
                    if (transform == "scale") {
                        ss >> x;
                        ss >> y;
                        ss >> z;

                        glm::vec3 coords(x, y, z);
                        object->scale(coords);
                        cout << "Scaling:"<< x <<","<< y <<","<< z <<endl;
                    } else if (transform == "rotate") {
                            
                        double angle;
                        ss >> angle;

                        ss >> x;
                        ss >> y;
                        ss >> z;

                        glm::vec3 coords(x, y, z);
                        object->rotate(angle,coords);
                        cout << "Rotating:"<< angle <<" axis:"<< x <<","<< y <<","<< z <<endl;

                    } else if (transform == "translate"){
                        ss >> x;
                        ss >> y;
                        ss >> z;

                        glm::vec3 coords(x, y, z);
                        object->translate(coords);
                        cout << "translating: "<< x <<","<< y <<","<< z <<endl;
                    } else {
                            cout << "Unknown transformation" << endl;
                    }
                }
            } else if (firstWord.length()<1){
            //empty lines
            } else cout << "???:"<<line <<endl;//print unknown lines
        }
        file.close();
    }else cout << "Unable to open file"; 
    
    return scene; 
}

Material SDFLoader::getMaterial(string name, std::vector<Material> data){
    return *find_if(
            data.begin(),
            data.end(),
            [name] (Material const & m) -> bool {
                return m.name == name;
            }
    );
}

LightPoint SDFLoader::getLight(string name, std::vector<LightPoint> data) {
     return *find_if(
            data.begin(),
            data.end(),
            [name] (LightPoint const& l) -> bool {
                return l.getName() == name;
            }
    );
}

std::shared_ptr<RenderObject> const& SDFLoader::getShape(string name, std::vector<std::shared_ptr<RenderObject>> data) {
    auto iter = std::find_if(
            data.begin(),
            data.end(),
            [&name](std::shared_ptr<RenderObject> const& ptr) -> bool {
                return ptr->getName() == name;
            }
    );
    if (data.end() == iter) {
        return std::shared_ptr<RenderObject>();
    }
    return *iter;
}
