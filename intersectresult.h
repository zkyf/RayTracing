#ifndef _LJX_INTERSECTRESULT_H
#define _LJX_INTERSECTRESULT_H

#include "ray.h"

struct IntersectResult
{
	bool hit;
	Vector point;

	IntersectResult() : hit(false), point() {}
};

#endif