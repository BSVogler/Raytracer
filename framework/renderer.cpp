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
#include <cmath>

using namespace std;

Renderer::Renderer(unsigned w, unsigned h, string const& file)
  : width_(w)
  , height_(h)
  , colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
{}

Renderer::Renderer(unsigned w, unsigned h, string const& file, string const& scenefile)
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
  //const size_t checkersize = 20;
  
  cout << "#####RENDERING####"<<endl;
  cout << "Resolution: "<<scene_.resX<<"x"<<scene_.resY<<endl;
  cout << "Camera: "<<scene_.camname<<endl;
  cout << "ambient light "<<scene_.amb<<endl;
  
  float d = -scene_.resX/tan(scene_.camera.GetFovX()*M_PI/180); //apply camera fov, little different angle for each pixel
          
  for (unsigned y = 0; y < scene_.resY; ++y) {
      cout <<endl;
    for (unsigned x = 0; x < scene_.resX; ++x) {
        Pixel p(x,y);
        p.color = scene_.amb;
        
        //p.color = Color(0.0, 1.0, float(x)/scene_.resY);
        Ray ray = Ray();
        ray.direction.x = (float) -scene_.resX/2+x; 
        ray.direction.y = (float) -scene_.resY/2+y;
        ray.direction.z = d;
       
        //ray.direction.z = -scene_.camera.GetFovX();//Should be calculated by regarding resolution. Take a look at slide 35!
        
        //cout << "Ray@("<<x<<"x"<<y<<"): "<<ray<<endl;
        
        //here should get the camera transofratmion applied
        cout << "[";
        for(auto iterator = scene_.renderObjects.begin(); iterator != scene_.renderObjects.end(); iterator++) {
            auto intersection = ((RenderObject*) iterator->second)->intersect(ray);
            if (intersection.first){
                cout << "#";
                p.color += ((RenderObject*) iterator->second)->getMaterial().getKa()
                         + ((RenderObject*) iterator->second)->getMaterial().getKd()
                         + ((RenderObject*) iterator->second)->getMaterial().getKs();
            }
        }
        cout << "]";
        write(p);
    }
  }
  //ppm_.save(filename_);
}

void Renderer::write(Pixel const& p) {
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
    cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << endl;
  } else {
    colorbuffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}
