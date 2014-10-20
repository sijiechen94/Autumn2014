#include "math.h"
#include "stdio.h"
#include "stdlib.h"

double aerf(double input){
	double x=input>0?input:-input;
	double low=0,high=10;
	for(int i=0;i<40;i++){
		if(x>erf((low+high)/2)) low=(low+high)/2;
		else high=(low+high)/2;
	}
	return (low+high)/2;
}

int main(){
	double x=0.9999999;
	for(int i=0;i<7;i++){
		printf("aerf:%.14lf,   x=%.7lf\n",aerf(x),x);
		x=x*10-9;
	}
	return 0;
}

