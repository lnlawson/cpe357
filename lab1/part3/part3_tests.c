#include <stdio.h>

#include "checkit.h"
#include "part3.h"

int arr1[5] = {1,2,3,4,5};
int arr2[8] = {1,2,3,4,5,6,7,8};

void test_calc_1()
{
   checkit_int(sum(arr1, 5), 15);
}

void test_calc_2()
{
	checkit_int(sum(arr2, 8), 36);
}

void test_calc()
{
   test_calc_1();
   test_calc_2();
}

int main(void)
{
   test_calc();

   return 0;
}
