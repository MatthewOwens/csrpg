/*
 * This is a simple header file that defines structs to represent
 * points in space. points can be comprised of 2-4 integers or
 * floats. This makes the header versitile as it can also be
 * used to store other data. For example: colour information
*/
#ifndef POINT_H
#define POINT_H
typedef struct { int x, y; } Point2i;
typedef struct { int x, y, z ; } Point3i;
typedef struct { int w, x, y , z; } Point4i;

typedef struct { float x, y; } Point2f;
typedef struct { float x, y, z; } Point3f;
typedef struct { float w, x, y, z; } Point4f;
#endif//POINT_H
