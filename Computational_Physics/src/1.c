#include "1.h"

static int32_t p=0x7FFFFFFF;
static int16_t a=16807;
static int32_t seed=0;

//Setting the seedd
void sschrage(int32_t s){
	if(seed<0) seed=-seed;
	seed=s;
}//sschrage

double schrage(){
	//Schrage's algorithm for generating next random number
	int32_t x_high=seed/0x10000;
	int32_t x_low=seed%0x10000;
	
	int32_t y_high=a*x_high;
	int32_t y_low=a*x_low;
	
	int32_t z=y_high%0x8000*0x10000+y_low;
	int32_t k=y_high/0x8000;

	if(p-z<k) seed=z-p+k;
	else seed=z+k;

	return seed/(double)SCHRAGE_MAX;
}//schrage
