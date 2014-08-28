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
    if (scene_.renderObjects.find("root")!= scene_.renderObjects.end()){
        cout << "#####RENDERING####"<<endl;
        cout << "Resolution: "<<scene_.resX<<"x"<<scene_.resY<<endl;
        cout << "Camera: "<<scene_.camname<<endl;
        cout << "ambient light "<<scene_.amb<<endl;

        float d = -scene_.resX/tan(scene_.camera.GetFovX()*M_PI/180); //apply camera fov, little different angle for each pixel

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
                } else {
                    Ray ray(glm::vec3(scene_.camera.GetTransformation_inv() * glm::vec4(0,0,0,1)));
                    ray.direction.x = -scene_.resX/2.0f+x; 
                    ray.direction.y = -scene_.resY/2.0f+y;
                    ray.direction.z = d;

                    //here should get the camera transformation applied
                    //ray.direction = glm::vec3(scene_.camera.GetTransformation_inv() * glm::vec4(ray.direction, 0));
                    
                    //cout << "Ray@("<<x<<"x"<<y<<"): "<<ray<<endl;

                    p.color +=getColor(ray);
                }
                p.color += scene_.amb;
                write(p);
            }
        }
        ppm_.save(scene_.outputFile);
        finished_ = true;
    } else {
        cout << "no root found!"<<endl;
    }
}

Color Renderer::getColor(const Ray& ray) {
    Color diff;
    
    auto intersection( scene_.renderObjects["root"]->intersect(ray) );

    if (intersection.hit){//if intersection happened
        //starting from the intersection go to every light source
        for(auto lightIt = scene_.lights.begin(); lightIt != scene_.lights.end(); lightIt++) {
            auto light = lightIt->second;
            //a ray pointing to the current light source
            auto lightRay = Ray(
                intersection.ray.origin,
                glm::normalize(light.GetPos()-intersection.ray.origin)//l=IL =L-I 
            );
            lightRay.origin += lightRay.direction/100.0f;//don't collide with itself
            
            //shaddow
            auto lighintersect = scene_.renderObjects["root"]->intersect(lightRay);
            if (!(lighintersect.hit && lighintersect.distance < glm::length(light.GetPos()-intersection.ray.origin))){//check if intersec between p and light source
                //diffuse light
                double fDiffuse = glm::dot(lightRay.direction, intersection.ray.direction);//l*n
                fDiffuse = fDiffuse < 0 ? 0 : fDiffuse;//allow no negative diffuse light

                diff +=  light.GetDiff()//get light color
                        * intersection.material.getKd()//multiply by material, (l_p * k_d)
                        * fDiffuse;
            }
        }
    }
    return diff;
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
