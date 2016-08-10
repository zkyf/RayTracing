#ifndef _LJX_INTERSECTRESULT_H
#define _LJX_INTERSECTRESULT_H

#include "ray.h"

struct IntersectResult
{
	bool hit;
	Vector point;
	double distance;
	Vector normal;
  Vector color;

	IntersectResult() : hit(false), point() {}
};

#endif