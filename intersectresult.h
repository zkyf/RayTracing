#ifndef _LJX_INTERSECTRESULT_H
#define _LJX_INTERSECTRESULT_H

#include "ray.h"
#include "color.h"

struct IntersectResult
{
	bool hit;
	Vector point;
	double distance;
	Vector normal;
  Color color;

	IntersectResult() : hit(false), point() {}
};

#endif