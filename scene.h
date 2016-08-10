#ifndef _LJX_SCENE_H
#define _LJX_SCENE_H

#include "objects.h"
#include "camera.h"
#include <iostream>
#include <vector>

using namespace std;

struct Scene
{
  vector<Item*> items;
  //vector<Light> lights;

  Mat shade(int width, int height, Camera camera, double maxdepth = 5.0f)
  {
    Mat scene(height, width, CV_8UC3, Scalar::all(0));
    double x = 0, y = 0;
    for (int i = 0; i < width; i++)
    {
      x = i*1.0 / width - 0.5;
      for (int j = 0; j < height; j++)
      {
        y = 0.5 - j*1.0 / height;
        Ray ray = camera.genRay(x, y);
        IntersectResult result; result.hit = false;
        for (int k = 0; k < items.size(); k++)
        {
          IntersectResult temp = items[k]->intersect(ray);
          if (temp.hit && (temp.distance < result.distance || result.hit == false))
          {
            result = temp;
          }
        }
        if (result.hit)
        {
          double depth_color = (result.distance > maxdepth) ? 0 : 255 - result.distance * 255 / maxdepth;
          scene.at<Vec3b>(j, i)[0] = result.normal.x *127 + 128;
          scene.at<Vec3b>(j, i)[1] = result.normal.y * 127 + 128;
          scene.at<Vec3b>(j, i)[2] = result.normal.z * 127 + 128;
        }
      }
    }
    return scene;
  }

  void push(Item& item) { items.push_back(&item); }
};

#endif