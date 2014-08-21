/*
* File:   SDFLoader.hpp
* Author: Benedikt Vogler
*
* Created on 8. Juli 2014, 18:52
*/

#ifndef SDFLOADER_HPP
#define	SDFLOADER_HPP

#include "Scene.hpp"

class SDFLoader {
public:
	SDFLoader();
	SDFLoader(const SDFLoader& orig);
	static Scene load(std::string const& scenefile);
	virtual ~SDFLoader();
private:
};

#endif	/* SDFLOADER_HPP */

