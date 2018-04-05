#include "part6.h"

Point create_point(double x, double y)
{
   Point p = {x, y};
   return p;
}

int is_a_square(Rectangle rec)
{
	int left = rec.top_left.y - rec.bottom_right.y; 
	int bot = rec.top_left.x - rec.bottom_right.x; 	

	if (left == bot)
		return 1;

	return 0;
}