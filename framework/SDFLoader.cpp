/* 
 * File:   SDFLoader.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 8. Juli 2014, 18:52
 */

#include "SDFloader.hpp"
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
                //extract name
                int i = 16;
                //find next space
                while (line.at(i)!=' ') {
                    i++;
                }
                    
                string name = line.substr(16,i-16);
                
                //extract color
                Color ca(atoi(line.substr(16,1).c_str()), atoi(line.substr(18,1).c_str()), atoi(line.substr(19,1).c_str()));
                Color cd(atoi(line.substr(16,1).c_str()), atoi(line.substr(18,1).c_str()), atoi(line.substr(19,1).c_str()));
                Color cs(atoi(line.substr(16,1).c_str()), atoi(line.substr(18,1).c_str()), atoi(line.substr(19,1).c_str()));
                float m = atoi(line.substr(39,1).c_str());
                Material mat(ca, cd, cs,m, name);
                cout << "Found material:"<<mat<<endl;
                mvec.push_back(mat);
            } else
                cout << line <<endl;
        }
        file.close();
    }else cout << "Unable to open file"; 
    
    return Scene(mvec); 
}



