// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------
#define _USE_MATH_DEFINES

#include "renderer.hpp"
#include "SDFloader.hpp"
#include "ray.hpp"
#include <cmath>
#include <glm/glm.hpp>

using namespace std;

Renderer::Renderer(unsigned w, unsigned h)
  : width_(w)
  , height_(h)
  , colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
  , scenefile_("scene.sdf")
  , ppm_(width_, height_)
  ,finished_(false)
{
    scene_ = SDFLoader::load(scenefile_);
}

Renderer::Renderer(unsigned w, unsigned h, string const& scenefile)
  : width_(w)
  , height_(h)
  , colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
  , scenefile_(scenefile)
  , ppm_(width_, height_)
  ,finished_(false)
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
    if (SDFLoader::getShape("root",scene_.renderObjects) != nullptr ){
        cout << "#####RENDERING####"<<endl;
        cout << "Resolution: "<<scene_.resX<<"x"<<scene_.resY<<endl;
        cout << "Camera: "<<scene_.camname<<endl;
        cout << "ambient light "<<scene_.amb<<endl;

        float d = -int(scene_.resX)/tan(scene_.camera.GetFovX()*M_PI/180); //apply camera fov, little different angle for each pixel

        for (unsigned yr = 0; yr < scene_.resY; ++yr) {
            for (unsigned xr = 0; xr < scene_.resX; ++xr) {
                unsigned x=xr;
                unsigned y=yr;
                
                //allow random pixel rendering
                if (scene_.random){
                    x=rand() % scene_.resX;
                    y=rand() % scene_.resY;
                    for (int i = 0; i < 100; i++) {//try 100 times
                        auto coloratp = colorbuffer_[(width_*y + x)];
                        if (!(coloratp.r == 0 && coloratp.g==0 && coloratp.b==0)){//again if already filled
                            x=rand() % scene_.resX;
                            y=rand() % scene_.resY;
                        }else break;
                    }
                }
                
                Pixel p(x,y);

               
                //Ray ray(glm::vec3(scene_.camera.GetTransformation() * glm::vec4(0,0,0,1)));
                Ray ray;
                ray.direction.x = -int(scene_.resX)/2.0f+x; 
                ray.direction.y = -int(scene_.resY)/2.0f+y;
                ray.direction.z = d;
                
                //apply camera transformations
                ray.origin = glm::vec3(scene_.camera.GetTransformation_inv() * glm::vec4(ray.origin, 1));
                ray.direction = glm::vec3(scene_.camera.GetTransformation_inv() * glm::vec4(ray.direction, 0));
                        
                if (scene_.antialiase>0){//SSAA
                    int samples = sqrt(scene_.antialiase);
                    for (int xAA=1;xAA<samples+1;++xAA){
                        for (int yAA=1;yAA<samples+1;++yAA){
                            Ray aaRay;
                            aaRay.direction.x = ray.direction.x +(float) (xAA)/(float)samples-0.5f; 
                            aaRay.direction.y = ray.direction.y +(float) (yAA)/(float)samples-0.5f;
                            aaRay.direction.z = d;
                            p.color +=getColor(aaRay);
                        }
                    }
                }


                //cout << "Ray@("<<x<<"x"<<y<<"): "<<ray<<endl;
                if (scene_.antialiase>0)
                    p.color /=scene_.antialiase;
                else
                    p.color +=getColor(ray);
                write(p);
            }
        }
        ppm_.save(scene_.outputFile);
        finished_ = true;
    } else {
        cout << "no root found!"<<endl;
    }
}

Color Renderer::getColor(Ray const& ray) {
    Color clr;
    
    auto intersection= (SDFLoader::getShape("root", scene_.renderObjects))->intersect(ray);

    if (intersection.hit){//if intersection happened
        clr +=scene_.amb*intersection.material.ka;//ambient light
        
        //starting from the intersection go to every light source
        for(auto& light : scene_.lights) {
            //a ray pointing to the current light source
            auto lightRay = Ray(
                intersection.ray.origin,    //start at intersection point
                glm::normalize(light.getPos()-intersection.ray.origin)//l=IL =L-I 
            );
            lightRay.maxt = glm::length(light.getPos()-lightRay.origin);
            
            //shaddow
            auto lighintersect = SDFLoader::getShape("root",scene_.renderObjects)->intersect(lightRay);
            if (!(lighintersect.hit)){//check if intersec between p and light source
                //diffuse light
                double fDiffuse = glm::dot(lightRay.direction, intersection.ray.direction);//l*n
                fDiffuse = fDiffuse < 0 ? 0 : fDiffuse;//allow no negative diffuse light

                clr +=  light.getDiff()//get light color
                        * intersection.material.kd//multiply by material, (l_p * k_d)
                        * fDiffuse
                        * intersection.material.opac;
                
                
                auto r = glm::normalize(
                            glm::reflect(
                                lightRay.direction,
                                intersection.ray.direction
                            )
                        );
                Color spec = light.getDiff()
                       * intersection.material.ks
                       * glm::pow(
                            glm::dot(r, glm::normalize(ray.direction)),
                            intersection.material.m
                        );//(l*r)^m
                if (spec.r<0) spec.r=0;
                if (spec.g<0) spec.g=0;
                if (spec.b<0) spec.b=0;
                clr +=spec*intersection.material.opac; 
            }
             //refraction
            if (intersection.material.opac < 1.0f){
                auto refrdir = glm::refract(ray.direction, intersection.ray.direction, intersection.material.refr);
                clr += getColor(
                        Ray(
                            intersection.ray.origin,    //start at intersection point
                            refrdir
                        )
                    )*(1.0f-intersection.material.opac);
            }
        }
    }
    return clr;
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
