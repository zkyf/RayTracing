#include "raytracing.h"

int main()
{
  double angle = 0;
	Camera camera;
  camera.pos = Vector(0, 0, 4);
  Sphere s1(Vector(-3, 0, 0), 1); s1.kd = Color(255, 0, 0);
  Sphere s2(Vector(0, 0, 0), 1); s2.kd = Color(0, 255, 0);
  Sphere s3(Vector(3, 0, 0), 1); s3.kd = Color(0, 0, 255);
  PointLight l1; l1.pos = Vector(-5, 5, 0);
  Item i1;
  i1.push(s1);
  i1.push(s2);
  i1.push(s3);
  Scene scene;
  scene.push(i1);
  scene.push(l1);
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