#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415926535897932384626
#endif

#define SEED 0.000001		//Initial value used for trajectory plotting
#define SIZE 256		//Times to iterate
#define LAMBDA_MAX 5.0		
#define LAMBDA_MIN 0		
#define NUM_OF_LAMBDA 10001	
#define SEED1 1E-7		//One of initial value used for computing Lyapunov's exponent
#define SEED2 2E-7 		//One of initial value used for computing Lyapunov's exponent

double fun(double x, double arg){
	return arg*sin(M_PI*x);
}//Iteration function

void iteration(double seed, double arg, double (*fun)(double,double), double* result){
	double y=seed;
	for(int i=0;i<SIZE;i++){
		result[i]=y;
		y=fun(y,arg);
	}
}//Iteration process

void lyapunov(double seed1, double seed2, double arg, double (*fun)(double,double), double* result){
	double ds;
	double y1=seed1;
	double y2=seed2;
	double logsum=0;
	for(int i=0;i<SIZE;i++){

		//Iterate
		ds=y2-y1;
		y1=fun(y1,arg);
		y2=fun(y2,arg);
		logsum+=log(fabs((y2-y1)/ds));
		
		//Float exception handling
		if(isnan(logsum)){
			fprintf(stderr,"Warning:NaN encountered!\nProcess:logsum\tds=%19.16lf,dy=%19.16lf\n",ds,y2-y1);
			*result=0;
			return ;
		}
		if(isinf(logsum)){
			fprintf(stderr,"Warning:Infinity encountered!\nProcess:logsum\tds=%19.16lf,dy=%19.16lf\n",ds,y2-y1);
			*result=0;
			return ;
		}

		//Renormalize
		y2=y1+ds;
	}

	//Average
	*result=logsum/SIZE;
}

int main(int argc, const char* argv[]){
	
	//File and memory handling
	FILE *fp1,*fp2;
	if(!(fp1=fopen("iterationtrajectory.txt","w"))){fprintf(stderr,"FOPEN ERROR!\n");exit(0);}
	if(!(fp2=fopen("lyapunov.txt","w"))){fprintf(stderr,"FOPEN ERROR!\n");exit(0);}
	double *result,*lyapunovexponent;
	if(!(result=malloc(SIZE*sizeof(double)))){fprintf(stderr,"MALLOC ERROR!\n");exit(0);}
	if(!(lyapunovexponent=malloc(NUM_OF_LAMBDA*sizeof(double)))){fprintf(stderr,"MALLOC ERROR!\n");exit(0);}
	
	//Write an array for plotting, a number as Lyapunov's exponent
	for(int i=0;i<NUM_OF_LAMBDA;i++){
		double lambda=(LAMBDA_MAX-LAMBDA_MIN)/(NUM_OF_LAMBDA-1)*i+LAMBDA_MIN;
		iteration(SEED,lambda,fun,result);
		lyapunov(SEED1,SEED2,lambda,fun,lyapunovexponent+i);
		fwrite(result,sizeof(double),SIZE,fp1);
	}
	fwrite(lyapunovexponent,sizeof(double),NUM_OF_LAMBDA,fp2);

	return 0;
}
