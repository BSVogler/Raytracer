/*
* File:   Material.cpp
* Author: Benedikt Vogler
*
* Created on 4. Juli 2014, 20:29
*/

#include "Material.hpp"

std::ostream& operator<<(std::ostream& os, Material const& mat)
{
	os << "name: \"" << mat.getName() << "\"" << std::endl
		<< "ka: " << mat.getKa() << std::endl
		<< "kd: " << mat.getKd() << std::endl
		<< "ks: " << mat.getKs() << std::endl
		<< "m: " << mat.getM() << std::endl;
	return os;
}


