#include "raytracing.h"

int main()
{
  double angle = 0;
	Camera camera;
  camera.pos = Vector(0, 0, 4);
	Sphere s1(Vector(-0.5, 0, 0), 1);
  Sphere s2(Vector(0.5, 0, 0), 1);
  Item i1;
  i1.push(s1);
  i1.push(s2);
  Scene scene; scene.push(i1);
  while (1)
  {
    Mat display = scene.shade(480, 480, camera);
    imshow("display", display);
    waitKey(10);
    angle += M_PI / 180;
    camera.pos = Vector(4 * sin(angle), 0, 4 * cos(angle));
    camera.right = Vector(cos(angle), 0, -sin(angle));
  }
}