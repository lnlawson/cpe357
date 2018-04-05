
#include <stdio.h>
#include "checkit.h"
#include "part4.h"

char arr1[] = {'H','e','L','L','o','\0'};
char arr12[6];
char arr123[6] = "hello";

char arr2[] = {'L','O','g','A','N',',',' ','H','I','\0'};
char arr22[10];
char arr223[10] = "logan, hi";

void test_lower_1()
{
   lower(arr1, arr12);
   checkit_string(arr12, arr123);
}

void test_lower_2()
{
   lower(arr2, arr22);
   checkit_string(arr22, arr223);
}

void test_lower_M_1()
{
   lower_mutate(arr1);
   checkit_string(arr1, arr123);
}

void test_lower_M_2()
{
   lower_mutate(arr2);
   checkit_string(arr2, arr223);
}

void test_lower()
{
   test_lower_1();
   test_lower_2();
}

void test_lower_mutate()
{
	test_lower_M_1();
	test_lower_M_2();
}

int main(void)
{
   test_lower();
   test_lower_mutate();

   return 0;
}
