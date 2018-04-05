/*Name: Logan Lawson
 *Lab 1 : Part 3*/

#include "part3.h"

int sum(int arr[], int length){
	int res = 0;
	int i;

	for(i = 0; i < length; i++){
		res += arr[i];
	}
	return res;
}