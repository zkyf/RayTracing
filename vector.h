#include <iostream>
using namespace std;

#define _USE_MATH_DEFINES
#include <math.h>

#ifndef _LJX_VECTOR_H
#define _LJX_VECTOR_H

#ifndef EPS
#define EPS (1E-13)
#endif

struct Vector
{
	double x, y, z; // Position of the vector

	Vector() : x(0), y(0), z(0) {}
	Vector(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

	double length() { return sqrt(x*x + y*y + z*z); }
	Vector inv() { return Vector(-x, -y, -z); }
	Vector unit() { double len = length(); return Vector(x / len, y / len, z / len); }

	Vector operator+(Vector& b) { return Vector(x + b.x, y + b.y, z + b.z); }
	Vector operator-(Vector& b) { return Vector(x - b.x, y - b.y, z - b.z); }
	double operator*(Vector& b) { return x*b.x + y*b.y + z*b.z; }
	Vector operator*(double& b) { return Vector(x*b, y*b, z*b); }
};


#endif