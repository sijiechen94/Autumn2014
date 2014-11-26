#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXREPT 25
#define EPSILON 1e-2

int verbose=0;

double fun2(double x){
	return pow(x,5)-9;
}

double dfun2(double x){
	return 5*pow(x,4)-9;
}

double fun(double x){
	return pow(x,3)/3.0-x;
}

double dfun(double x){
	return x*x-1;
}

double g(double x, double (*fun)(double), double (*dfun)(double)){
	double rv=x-fun(x)/dfun(x);
	if(verbose) printf("g(%lf)=%lf\n",x,rv);
	return rv;
}

double h(double x0, double x1, double (*fun)(double)){
	double rv=x1-fun(x1)*(x1-x0)/(fun(x1)-fun(x0));
	if(verbose) printf("h(%lf,%lf)=%lf\n",x0,x1,rv);
	return rv;
}

int call_Newtonian(double x0, double (*fun)(double), double (*dfun)(double), double* result){
	double x1;
	for(int i=0;i<MAXREPT;i++){
		x1=g(x0,fun,dfun);
		if(fabs(x1-x0)<EPSILON){	//Success
			*result=x1;
			return 0;
		}
		x0=x1;
	}
	return -1;				//Failure
}


int call_Secant(double x0, double x1, double (*fun)(double), double* result){
	double x2;
	for(int i=0;i<MAXREPT;i++){
		x2=h(x0,x1,fun);
		if(fabs(x2-x0)<EPSILON||fabs(fun(x2))<EPSILON){	//Success
			*result=x2;
			return 0;
		}
		x0=x1;
		x1=x2;
	}
	return -1;				//Failure
}
	

int main(int argc, const char* argv[]){
	
	if(argc==2) if(strcmp(argv[1],"--verbose")==0) verbose=1;
	int err=0;
	double x[4]={2.0,2.0,2.0,2.0};
	double result;
	printf("Calling Newtonian\n");
	for(int i=0;i<4;i++){
		err=call_Newtonian(x[i],fun2,dfun2,&result);
		if(err!=0)printf("Warning!Newtonian didn't find a root!\n");
		else printf("Newtonian:\tRoot around %lf is %19.16lf\n",x[i],result);
	}

	printf("Calling Secant\n");
	for(int i=0;i<4;i++){
		err=call_Secant(-x[i],x[i],fun2,&result);
		if(err!=0)printf("Warning!Secant didn't find a root!\n");
		else printf("Secant:\t\tRoot around %lf is %19.16lf\n",x[i],result);
	}

	return 0;
}
