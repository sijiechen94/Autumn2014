#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "limits.h"

static int16_t d=0x20-1;
static int32_t p=0x80000000-1;
static int16_t a=16807;

int32_t schrage(int32_t seed){
	if(seed<0) seed=-seed;
	static int cc=0;
	if(!cc){
		cc++;
	}	
	
	int32_t x_high=seed/0x10000;
	int32_t x_low=seed%0x10000;
	
	int32_t y_high=a*x_high;
	int32_t y_low=a*x_low;
	
	int32_t z=y_high%0x8000*0x10000+y_low;
	int32_t k=y_high/0x8000;

	if(p-z<k) return z-p+k;
	else return z+k;
}
