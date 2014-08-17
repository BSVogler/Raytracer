// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#include "SDFloader.hpp"
#include "ray.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
{}

Renderer::Renderer(unsigned w, unsigned h, std::string const& file, std::string const& scenefile)
  : width_(w)
  , height_(h)
  , colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , scenefile_(scenefile)
  , ppm_(width_, height_)
{
   scene_ = SDFLoader::load(scenefile);
}

void Renderer::render() {
  //const std::size_t checkersize = 20;
  
  std::cout << "#####RENDERING####"<<std::endl;
  std::cout << "Resolution: "<<scene_.resX<<"x"<<scene_.resY<<std::endl;
  std::cout << "Camera: "<<scene_.camname<<std::endl;
  std::cout << "ambient light "<<scene_.amb<<std::endl;
  
  for (unsigned y = 0; y < scene_.resY; ++y) {
    for (unsigned x = 0; x < scene_.resX; ++x) {
        Pixel p(x,y);
        p.color = scene_.amb;

        //p.color = Color(0.0, 1.0, float(x)/scene_.resY);
        Ray ray = Ray();
        ray.origin = scene_.camera.GetOrigin();//ray starts at camera
        ray.direction = scene_.camera.GetN();//ray moves in cameras looking direction
        //apply camera fov, little different angle for each pixel
        ray.direction.x -= tan(scene_.camera.GetFovX()*x/scene_.resX-scene_.camera.GetFovX())*ray.direction.z; 
        ray.direction.y -= tan(scene_.camera.GetFovX()*x/scene_.resY-scene_.camera.GetFovX())*ray.direction.z;
        
        typedef std::map<std::string, RenderObject*>::iterator it_type;
        for(it_type iterator = scene_.renderObjects.begin(); iterator != scene_.renderObjects.end(); iterator++) {
            auto intersection = iterator->second->intersect(ray);
            if (intersection.first)
                p.color += iterator->second->getMaterial().getKa();
        }
        write(p);
    }
  }
  //ppm_.save(filename_);
}

void Renderer::write(Pixel const& p) {
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    colorbuffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}
