#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>

struct Color
{
  Color(float red, float green, float blue) : r_(red), g_(green), b_(blue) {}
  float r_;
  float g_;
  float b_;

  friend std::ostream& operator<<(std::ostream& os, Color const& c)
  {
    os << "(" << c.r_ << "," << c.g_ << "," << c.b_ << ")\n";
    return os;
  }

  Color& operator+=(Color const& other)
  {
    r_ += other.r_;
    g_ += other.g_;
    b_ += other.b_;
    return *this;
  }

  Color& operator-=(Color const& other)
  {
    r_ -= other.r_;
    g_ -= other.g_;
    b_ -= other.b_;
    return *this;
  }

  friend Color operator+(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp += b;
    return tmp;
  }

  friend Color operator-(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp -= b;
    return tmp;
  }
};

#endif //#define BUW_COLOR_HPP
