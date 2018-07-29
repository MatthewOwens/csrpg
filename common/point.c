#include "point.h"

Point2i point2i(int x, int y)
{
	Point2i p;
	p.x = x;
	p.y = y;
	return p;
}
Point3i point3i(int x, int y, int z)
{
	Point3i p;
	p.x = x;
	p.y = y;
	p.z = z;
	return p;
}
Point4i point4i(int w, int x, int y, int z)
{
	Point4i p;
	p.w = w;
	p.x = x;
	p.y = y;
	p.z = z;
	return p;
}

Point2f point2f(float x, float y)
{
	Point2f p;
	p.x = x;
	p.y = y;
	return p;
}
Point3f point3f(float x, float y, float z)
{
	Point3f p;
	p.x = x;
	p.y = y;
	p.z = z;
	return p;
}
Point4f point4f(float w, float x, float y, float z)
{
	Point4f p;
	p.w = w;
	p.x = x;
	p.y = y;
	p.z = z;
	return p;
}
