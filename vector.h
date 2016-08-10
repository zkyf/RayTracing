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

	friend Vector operator+(Vector a, Vector b);
	friend Vector operator-(Vector a, Vector b);
	friend double operator*(Vector a, Vector b);
	friend Vector operator*(Vector a, double b);
	friend Vector operator*(double a, Vector b);
};

Vector operator+(Vector a, Vector b) { return Vector(a.x + b.x, a.y + b.y, a.z + b.z); }
Vector operator-(Vector a, Vector b) { return Vector(a.x - b.x, a.y - b.y, a.z - b.z); }
double operator*(Vector a, Vector b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
Vector operator*(Vector a, double b) { return Vector(a.x*b, a.y*b, a.z*b); }
Vector operator*(double a, Vector b) { return Vector(b.x*a, b.y*a, b.z*a); }

Vector CrossProduct(Vector a, Vector b)
{
	return Vector(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

#endif