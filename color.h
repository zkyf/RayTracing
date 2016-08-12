#ifndef _LJX_COLOR_H
#define _LJX_COLOR_H

struct Color
{
  int r, g, b;

  Color() : r(0), g(0), b(0) {}
  Color(int _r, int _g, int _b) : r(_r), g(_g), b(_b) {}

  void set(int _r, int _g, int _b)
  {
    r = _r; g = _g; b = _b;
    if (r < 0) r = 0; if (r>255) r = 255;
    if (g < 0) g = 0; if (g>255) g = 255;
    if (b < 0) b = 0; if (b>255) b = 255;
  }

  friend Color operator+(Color a, Color b);
  friend Color operator-(Color a, Color b);
  friend Color operator*(Color a, double b);
  friend Color operator*(double a, Color b);
  friend Color operator/(Color a, double b);
};

Color operator+(Color a, Color b)
{
  Color result;
  result.set(a.r + b.r, a.g + b.g, a.b + b.b);
  return result;
}

Color operator-(Color a, Color b)
{
  Color result;
  result.set(a.r - b.r, a.g - b.g, a.b - b.b);
  return result;
}

Color operator*(Color a, double b)
{
  Color result;
  result.set(a.r*b, a.g*b, a.b*b);
  return result;
}

Color operator*(double a, Color b)
{
  Color result;
  result.set(a*b.r, a*b.g, a*b.b);
  return result;
}

Color operator/(Color a, double b)
{
  return a*(1 / b);
}

#endif