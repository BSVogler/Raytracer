// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>

struct Color {
    
    Color(float red, float green, float blue):
      r(red),
      g(green),
      b(blue)
    {}

    Color():
      r(0),
      g(0),
      b(0)
    {}


    float r;
    float g;
    float b;

    friend std::ostream& operator<<(std::ostream& os, Color const& c){
      os << "(" << c.r << "," << c.g << "," << c.b << ")";
      return os;
    }

    Color& operator+=(Color const& other){
        r += other.r;
        g += other.g;
        b += other.b;
        return *this;
    }

    Color& operator-=(Color const& rsd){
        r -= rsd.r;
        g -= rsd.g;
        b -= rsd.b;
        return *this;
    }

    Color& operator/=(float rsd){
        r /= rsd;
        g /= rsd;
        b /= rsd;
        return *this;
    }

    Color& operator*=(float rsd){
        r *= rsd;
        g *= rsd;
        b *= rsd;
        return *this;
    }
    Color& operator*=(Color rsd){
        r *= rsd.r;
        g *= rsd.g;
        b *= rsd.b;
        return *this;
    }
    
  friend Color operator+(Color const& lsd, Color const& rsd){
    return Color(lsd)+=rsd;
  }

  friend Color operator-(Color const& lsd, Color const& rsd){
    return Color(lsd)-=rsd;
  }
  
  friend Color operator*(Color const& lsd, Color const& rsd){
    return Color(lsd)*=rsd;
  }
  
  friend Color operator*(Color const& lsd, float rsd){
    return Color(lsd)*=rsd;
  }
  
  friend Color operator*(float lsd, Color const& rsd ){
    return Color(rsd)*=lsd;
  }
  
  friend Color operator/(Color const& lsd, float rsd){
    return Color(lsd)/=rsd;
  }
};

#endif //#define BUW_COLOR_HPP
