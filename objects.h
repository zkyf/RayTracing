#include "intersectresult.h"

#ifndef _LJX_OBJECTS_H
#define _LJX_OBJECTS_H

struct Object
{
	virtual IntersectResult intersect(Ray ray) { return IntersectResult(); }
};

struct Plane : public Object
{
	Vector normal;
	double dist;
	
	Plane() : normal(), dist(0) {}
	Plane(Vector _normal, double _dist) : normal(_normal), dist(_dist) {}

	virtual IntersectResult intersect(Ray ray)
	{
		IntersectResult result; result.hit = false;
		Vector o = Vector() + normal.unit() * dist;
		double down = ray.dir * normal;
		if (fabs(down) > EPS)
		{
			result.hit = true;
			double t = (o - ray.from)*normal / down;
			result.point = ray.from + ray.dir*t;
		}
		return result;
	}
};

struct Triangle : public Object
{
	Vector a, b, c;

	Triangle(Vector _a, Vector _b, Vector _c) : a(_a), b(_b), c(_c) {}
	virtual IntersectResult intersect(Ray ray)
	{
		IntersectResult result; result.hit = false;

	}
};

struct Sphere : public Object
{
	Vector center;
	double radius;
};

#endif