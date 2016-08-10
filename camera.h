#include <opencv2\opencv.hpp>
#include <iostream>
#include "vector.h"

using namespace cv;
using namespace std;

#ifndef _LJX_CAMERA_H
#define _LJX_CAMERA_H

struct Camera
{
	Vector pos;
	Vector up;
	Vector right;
	int width, height;
	int format;

	Camera(Vector _pos = Vector(0, 0, 0), Vector _up = Vector(0, 1, 0), Vector _right = Vector(1, 0, 0),
				 int _width = 480, int _height = 480) :
		pos(_pos.unit()), up(_up.unit()), right(_right.unit()), width(_width), height(_height), format(CV_8UC3) {}
	Vector dir() { return CrossProduct(up, right); }
	virtual Mat shade();
};

struct PerspectiveCamera : public Camera
{
	virtual Mat shade()
	{
		Mat result = Mat(height, width, format, Scalar::all(0));

	}
};

struct ParallelCamera : public Camera
{

};

#endif