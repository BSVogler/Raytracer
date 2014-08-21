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

class Material {
public:
	Material() :
		ka(0, 0, 0), kd(0, 0, 0), ks(0, 0, 0)
	{};
	Material(Color ka, Color kd, Color ks, float m, std::string name) :
		ka(ka), kd(kd), ks(ks), m(m), name(name)
	{}

	std::string getName() const {
		return name;
	}

	Color getKa() const {
		return ka;
	}

	Color getKd() const {
		return kd;
	}

	Color getKs() const {
		return ks;
	}

	float getM() const {
		return m;
	}

private:
	std::string name;
	Color ka;
	Color kd;
	Color ks;
	float m;
};

std::ostream& operator <<(std::ostream& os, Material const& mat);

#endif	/* MATERIAL_HPP */

