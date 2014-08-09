/* 
 * File:   SDFLoader.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 8. Juli 2014, 18:52
 */

#include "SDFloader.hpp"
#include "Camera.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Material.hpp"
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
    std::cout << "Loading file: " << scenefile << std::endl;
    Scene scene = Scene();
    
    vector<Material> mvec;
    
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
                    int red, green, blue;
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
                    mvec.push_back(mat);
                } else if (tmpString=="camera"){
                    //scene.camera = Camera("test",150);
                }else
                    cout << "object to define not implemented:"<<ss.str() <<endl;
            } else if (tmpString=="render"){
                ss >> scene.camname;
                ss >> scene.outputFile;
                ss >> scene.resX;
                ss >> scene.resY;
                if (scene.resX<=0) scene.resX=100;
                if (scene.resY<=0) scene.resY=100;
                cout << "Scene should be rendered from "<< scene.camname << " at resolution "<<scene.resX<<"x"<< scene.resY<< " to "<<scene.outputFile<<endl;
            } else if (tmpString=="#"){
                cout << line << endl;
            } else
                cout << "Line not supported:"<<line <<endl;
        }
        file.close();
    }else cout << "Unable to open file"; 
    
    scene.materials = mvec;
    return scene; 
}



