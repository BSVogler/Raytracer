// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "Scene.hpp"
#include <string>
#include <glm/glm.hpp>

class Renderer {
public:
	Renderer(unsigned w, unsigned h);
	Renderer(unsigned w, unsigned h, std::string const& scenefile);

	void render();
	void write(Pixel const& p);
	void writeAlpha(Pixel const& p, float a);

	bool finished() const {
		return finished_;
	};

	inline std::vector<Color> const& colorbuffer() const {
		return colorbuffer_;
	}

private:
	unsigned width_;
	unsigned height_;
	std::vector<Color> colorbuffer_;
	std::string scenefile_;
	Scene scene_;
	PpmWriter ppm_;
	bool finished_;
	Color getColor(Ray const& ray);
};

#endif // #ifndef BUW_RENDERER_HPP
