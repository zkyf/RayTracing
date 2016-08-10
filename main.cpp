#include "raytracing.h"

int main()
{
  double angle = 0;
	Camera camera;
  camera.pos = Vector(0, 0, 4);
  Sphere s1(Vector(-0.5, 0, 0), 1); s1.kd = Vector(255, 0, 0);
  Sphere s2(Vector(0.5, 0, 0), 1); s2.kd = Vector(0, 255, 0);
  PointLight l1; l1.color = Vector(255, 255, 255); l1.pos = Vector(-2, 1, 0);
  Item i1;
  i1.push(s1);
  i1.push(s2);
  Scene scene; scene.push(i1); scene.push(l1);
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