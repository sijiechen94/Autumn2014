#include "stdio.h"
#include "stdlib.h"
#include "math.h"

long power(int base, int power){
        long v=base;
        for(int i=0; i<power; i++){
                v*=base;
        }   
        return v;
}

//Fun is pointer to given function to make these two functions genuine
double Cotes(double start, double end, double (*fun)(double), unsigned long N){
	
	//Apply summation
	double h=(end-start)/N;
	double I=(fun(start)+fun(end))/2;
	for(long j=1; j<N; j++)
		I+=fun(start+j*h);
	return I*h;
}

double Simpson(double start, double end, double (*fun)(double), unsigned long N){
	//Quit if N is not a even number
	if(N%2) {printf("Simpson: N is not even!\n"); exit(0);}

	//Apply summation
	double h=(end-start)/N;
	double I=fun(start)+fun(end)+4*fun(end-h);
	for(long j=1; j<N/2; j++)
		I+=4*fun(start+(2*j-1)*h)+2*fun(2*j*h+start);

	return I*h/3;
}

#define N_RANGE 13

int main(int argc, const char* argv[]){
	//Initialization
	double start=1,end=5;
	double* result;
	result=malloc(2*N_RANGE*sizeof(double));
	if(!result) {printf("MALLOC ERROR!\n"); exit(0);}
	
	//Computation and output
	printf("Cotes\t\tSimpson\n");
	for(int k=0; k<N_RANGE; k++){
		result[2*k]=Cotes(start,end,sin,(unsigned long)power(2,k));
		result[2*k+1]=Simpson(start,end,sin,(unsigned long)power(2,k));
		printf("%12.10lf\t%12.10lf\n",result[2*k],result[2*k+1]);
	}

	return 0;
}
