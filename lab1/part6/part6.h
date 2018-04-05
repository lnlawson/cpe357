#ifndef PART5_H
#define PART5_H
#include <math.h>

typedef struct point
{
   double x;
   double y;
}Point;

typedef struct rectangle
{
	Point top_left;
	Point bottom_right;
}Rectangle;

int is_a_square(Rectangle rec);

struct point create_point(double x, double y);

#endif
