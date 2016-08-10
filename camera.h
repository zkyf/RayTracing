#include <opencv2\opencv.hpp>
#include <iostream>
#include "vector.h"
#include "ray.h"

using namespace cv;
using namespace std;

#ifndef _LJX_CAMERA_H
#define _LJX_CAMERA_H

struct Camera
{
	Vector pos;
	Vector up;
	Vector right;
  double fov;
  double fscale;
  double front;

	Camera(Vector _pos = Vector(0, 0, 0), Vector _up = Vector(0, 1, 0), Vector _right = Vector(1, 0, 0),
				 int _width = 480, int _height = 480, double _fov = 90.0f) :
		pos(_pos), up(_up.unit()), right(_right.unit()), fov(_fov)
  {
    fscale = tan(fov* (M_PI  * 0.5f / 180)) * 2;
  }

	Vector dir() { return CrossProduct(up, right); }

  Ray genRay(double x, double y)
  {
    // The parameters are in the window coordinate system, with left-top as the origin
    Ray ray;
    ray.from = pos;
    ray.dir = dir() + x*fscale * right + y*fscale*up;
    return ray;
  }
};

#endif