#ifndef _LJX_LIGHT_H
#define _LJX_LIGHT_H

#include "vector.h"
#include "ray.h"

struct PointLight
{
  Vector pos;
  Vector color;
};

#endif