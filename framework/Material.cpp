/* 
 * File:   Material.cpp
 * Author: Benedikt Vogler
 * 
 * Created on 4. Juli 2014, 20:29
 */

#include "Material.hpp"

std::ostream& operator<<(std::ostream& os, Material const& mat)
{
  os << "name: \"" << mat.name <<"\"" << std::endl
     << "ka: " << mat.ka << std::endl
     << "kd: " << mat.kd << std::endl
     << "ks: " << mat.ks << std::endl
     << "m: " << mat.m << std::endl
     << "opac: " << mat.opac << std::endl
     << "refr: " << mat.refr << std::endl;
  return os; 
}


