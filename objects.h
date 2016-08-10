#include "intersectresult.h"

#ifndef _LJX_OBJECTS_H
#define _LJX_OBJECTS_H

#include <opencv2/opencv.hpp>

using namespace cv;

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
    Mat coe(3,3, CV_64F, Scalar::all(0));
    Mat res(3,1,CV_64F, Scalar::all(0));

    coe.at<double>(0, 0) = a.x - b.x;
    coe.at<double>(0, 1) = a.x - c.x;
    coe.at<double>(0, 2) = ray.dir.x;

    coe.at<double>(1, 0) = a.y - b.y;
    coe.at<double>(1, 1) = a.y - c.y;
    coe.at<double>(1, 2) = ray.dir.y;

    coe.at<double>(2, 0) = a.z - b.z;
    coe.at<double>(2, 1) = a.z - c.z;
    coe.at<double>(2, 2) = ray.dir.z;

    res.at<double>(0, 0) = a.x - ray.from.x;
    res.at<double>(1, 0) = a.y - ray.from.y;
    res.at<double>(2, 0) = a.z - ray.from.z;

    double deta = determinant(coe);
    
    coe.at<double>(0, 0) = res.at<double>(0, 0);
    coe.at<double>(1, 0) = res.at<double>(1, 0);
    coe.at<double>(2, 0) = res.at<double>(2, 0);
    double beta = determinant(coe) / deta;

    coe.at<double>(0, 0) = a.x - b.x;
    coe.at<double>(0, 1) = a.x - c.x;
    coe.at<double>(0, 2) = ray.dir.x;
    coe.at<double>(0, 1) = res.at<double>(0, 0);
    coe.at<double>(1, 1) = res.at<double>(1, 0);
    coe.at<double>(2, 1) = res.at<double>(2, 0);
    double gama = determinant(coe) / deta;

    if (beta > 0 && gama > 0 && beta + gama < 1)
    {
      result.hit = true;
      result.point = a + (b - a) * beta + (c - a) * gama;
    }

    return result;
	}
};

struct Sphere : public Object
{
	Vector center;
	double radius;

	virtual IntersectResult intersect(Ray ray)
	{
		IntersectResult result; result.hit = false;
		Vector diff = center - ray.from;
		double cosvalue = diff.unit() * ray.dir.unit();
		double sinvalue = sqrt(1 - cosvalue*cosvalue);
		double distance = diff.length() * sinvalue;
		if (cosvalue > 0 && distance < radius)
		{
			result.hit = true;
			result.point = ray.from + (diff*ray.dir.unit()) * ray.dir;
		}
		return result;
	}
};

#endif