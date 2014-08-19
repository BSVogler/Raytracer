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
#include <glm/glm.hpp>

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
  if (width_<scene_.resX){
      cout << "ERROR: Resolution X to big. Forcing: "<<width_<<endl;
      scene_.resX=width_;
  }
  if (height_<scene_.resY){
      cout << "ERROR: Resolution Y to big. Forcing: "<<height_<<endl;
      scene_.resY=height_;
  }
  cout << "#####RENDERING####"<<endl;
  cout << "Resolution: "<<scene_.resX<<"x"<<scene_.resY<<endl;
  cout << "Camera: "<<scene_.camname<<endl;
  cout << "ambient light "<<scene_.amb<<endl;
  
  float d = -scene_.resX/tan(scene_.camera.GetFovX()*M_PI/180); //apply camera fov, little different angle for each pixel
          
  for (unsigned y = 0; y < scene_.resY; ++y) {
    for (unsigned x = 0; x < scene_.resX; ++x) {
        Pixel p(x,y);
        if (scene_.antialiase>0){//SSAA
            
            for (int xSSAA=1;xSSAA<sqrt(scene_.antialiase)+1;++xSSAA){
                for (int ySSAA=1;ySSAA<sqrt(scene_.antialiase)+1;++ySSAA){
                    Ray ray = Ray();
                    ray.direction.x = -scene_.resX/2.0f+x+(float) (xSSAA/(float)sqrt(scene_.antialiase))-0.5f; 
                    ray.direction.y = -scene_.resY/2.0f+y+(float) (ySSAA/(float)sqrt(scene_.antialiase))-0.5f;
                    ray.direction.z = d;
                    p.color +=getColor(ray);
                }
            }
            p.color /=scene_.antialiase;
            p.color += scene_.amb;
        } else {
            Ray ray = Ray();
            ray.direction.x = -scene_.resX/2.0f+x; 
            ray.direction.y = -scene_.resY/2.0f+y;
            ray.direction.z = d;

            //here should get the camera transformation applied

            //cout << "Ray@("<<x<<"x"<<y<<"): "<<ray<<endl;

            p.color +=scene_.amb+getColor(ray);
        }
        write(p);
    }
  }
  //ppm_.save(filename_);
}

Color Renderer::getColor(const Ray& ray) {
    for(auto renderObjectIt = scene_.renderObjects.begin(); renderObjectIt != scene_.renderObjects.end(); renderObjectIt++) {//every render object
        auto intersection(((RenderObject*) renderObjectIt->second)->intersect(ray));
        if (intersection.first){//if intersection happened
            //starting from the intersection go to every light source
            for(auto lightIt = scene_.lights.begin(); lightIt != scene_.lights.end(); lightIt++) {
                auto light = lightIt->second;
                //a ray pointing to the current light source
                auto lightRay = Ray(
                    intersection.second.origin,
                    glm::normalize(light.GetPos()-intersection.second.origin)
                );
                //diffuse light
                return light.GetDiff() * ((RenderObject*) renderObjectIt->second)->getMaterial().getKd()
                        *glm::dot(lightRay.direction,intersection.second.direction);
            }
        }
    }
    return Color();
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
