/* 
 * File:   Material.hpp
 * Author: Benedikt Vogler
 *
 * Created on 4. Juli 2014, 20:29
 */

#ifndef MATERIAL_HPP
#define	MATERIAL_HPP

#include <string>
#include <iostream>
#include <ostream>
#include "color.hpp"

struct Material {
public:
    Material():
        ka(0,0,0),kd(0,0,0),ks(0,0,0)
    {};
    Material(Color ka, Color kd, Color ks, float m, float opac,float refr, std::string name) :
        ka(ka), kd(kd), ks(ks), m(m), name(name), refr(refr), opac(opac)
    {
        if (opac<=0.0f) this->opac=1.0f;
    }

    std::string name;
    Color ka;
    Color kd;
    Color ks;
    float m;
    float refr;
    float opac;
};

std::ostream& operator <<(std::ostream& os, Material const& mat);

#endif	/* MATERIAL_HPP */

