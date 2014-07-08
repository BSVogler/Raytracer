/* 
 * File:   SDFLoader.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 8. Juli 2014, 18:52
 */

#include "SDFLoader.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "Material.hpp"
using namespace std;

SDFLoader::SDFLoader() {
}

SDFLoader::SDFLoader(const SDFLoader& orig) {
}

SDFLoader::~SDFLoader() {
}

Scene SDFLoader::load(const string& scenefile) {
    std::cout << "Loading file: " << scenefile << std::endl;
    
    vector<Material> mvec;
    
    string line;
    ifstream file(scenefile);
    //file.open(scenefile, ios::in);
    if (file.is_open()) {
        
        while (getline (file,line)){
            if (line.substr(0,15)=="define material"){
                string name = "material";
                Color ca(atoi(line.substr(16,1).c_str()), atoi(line.substr(18,1).c_str()), atoi(line.substr(19,1).c_str()));
                Color cd(atoi(line.substr(16,1).c_str()), atoi(line.substr(18,1).c_str()), atoi(line.substr(19,1).c_str()));
                Color cs(atoi(line.substr(16,1).c_str()), atoi(line.substr(18,1).c_str()), atoi(line.substr(19,1).c_str()));
                float m = atoi(line.substr(39,1).c_str());
                cout << "Found material \""<<name<<"\" "<<ca<<","<<cd<<","<<cs<<"m:"<<m<<endl;
                mvec.push_back(Material(ca, cd, cs,m, name));
            } else
                cout << line <<endl;
        }
        file.close();
    }else cout << "Unable to open file"; 
    
    return Scene(mvec); 
}



