#ifndef _LJX_SCENE_H
#define _LJX_SCENE_H

#include "objects.h"
#include "camera.h"
#include "light.h"
#include <iostream>
#include <vector>

using namespace std;

struct Scene
{
  vector<Item*> items;
  vector<PointLight*> lights;

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
        int objectnum = -1;
        for (int k = 0; k < items.size(); k++)
        {
          IntersectResult temp = items[k]->intersect(ray);
          if (temp.hit && (temp.distance < result.distance || result.hit == false))
          {
            result = temp;
            objectnum = k;
          }
        }
        Vector color;
        if (result.hit)
        {
          color = result.color;
        }
        if (lights.size()>0)
        {
          for (int ln = 0; ln<lights.size(); ln++)
          {
            Ray shadowray;
            shadowray.from = lights[ln]->pos;
            shadowray.dir = (result.point - lights[ln]->pos).unit();
            bool shadow = false;
            for (int in = 0; in<items.size(); in++)
            {
              if (in == objectnum) continue;
              IntersectResult temp = items[in]->intersect(shadowray);
              if (temp.hit) { shadow = true; break; }
            }
            if (shadow) color = Vector(0, 0, 0);
            else color = color*(-1 * result.normal*shadowray.dir > 0 ? -1 * result.normal*shadowray.dir: 0);
          }
        }
        {
          double depth_color = (result.distance > maxdepth) ? 0 : 255 - result.distance * 255 / maxdepth;
          scene.at<Vec3b>(j, i)[0] = color.x;
          scene.at<Vec3b>(j, i)[1] = color.y;
          scene.at<Vec3b>(j, i)[2] = color.z;
        }
      }
    }
    return scene;
  }

  void push(Item& item) { items.push_back(&item); }
  void push(PointLight& light) { lights.push_back(&light); }
};

#endif