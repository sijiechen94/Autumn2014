#include "math.h"
#include "stdio.h"
#include "stdlib.h"

#define ARC4RANDOM_MAX 0x100000000                              //arc4random() returns 0~2**32-1
#define foo4random() ((double)arc4random()/ARC4RANDOM_MAX)      //convert uint32_t to double

#define SIZE 0x1000
#define Gauss(x) (M_2_SQRTPI/M_SQRT2/2.0*exp(-(x)*(x)/2))
#define Cauchy(x) (1.0/M_PI/(1+(x)*(x)))
#define ALPHA M_PI_2

int main(){
	
	double *vector;
	int i=0;
	vector=malloc(SIZE*sizeof(double));
	while(1){
		long u=arc4random()%840000;
		double pu=u>=266000?(u-266000)/41000+2995:u/2700
		double v=foo4random();
		if(v<Gauss(u)/ALPHA/Cauchy(u))    //Success
			vector[i++]=u;
		if(i==SIZE) break;
	}
	fwrite(vector,sizeof(double),SIZE,stdout);
	return 0;
}
			
		
		
