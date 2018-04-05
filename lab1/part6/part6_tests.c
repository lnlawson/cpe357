#include <stdio.h>

#include "checkit.h"
#include "part6.h"

/* define testing functions */
int res;

void test_create_point1(void)
{
   struct point p = create_point(1.9, -2.7);

   checkit_double(p.x, 1.9);
   checkit_double(p.y, -2.7);
}

void test_create_point2(void)
{
   struct point p = create_point(0.2, 12.1);

   checkit_double(p.x, 0.2);
   checkit_double(p.y, 12.1);
}

void test_is_square_1(void)
{
   Rectangle rec;
   rec.top_left = create_point(2,2);
   rec.bottom_right = create_point(0,0);
   res = is_a_square(rec);
   checkit_int(res, 1);
}

void test_is_square_2(void)
{
   Rectangle rec;
   rec.top_left = create_point(4,4);
   rec.bottom_right = create_point(2,2);
   res = is_a_square(rec);
   checkit_int(res, 1);
}

void test_create_point(void)
{
   test_create_point1();
   test_create_point2();
}

void test_is_square()
{
   test_is_square_1();
   test_is_square_2();
}

int main(int arg, char *argv[])
{
   /* call testing function(s) here */
   test_create_point();
   test_is_square();

   return 0;
}
