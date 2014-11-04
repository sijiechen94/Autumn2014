#include "stdio.h"
#include "stdlib.h"
#include "Mintegral.h"
#include <math.h>

#define SIZE 1000000000

double fun1(unsigned int dim, double* v){
	double x=*v;
	return sqrt(x+sqrt(x));
}

double fun2(unsigned int dim, double* v){
	return 6-v[0]*v[0]-v[1]*v[1]-v[2]*v[2]-v[3]*v[3]-v[4]*v[4];;
}

double MonteCarloInt(unsigned int dim, RANGE* ranges, double (*fun)(unsigned int,double*)){
	double sum=0;
	double* v;
	double vol=1;
	for(int j=0;j<dim;j++) vol*=(ranges[j].end-ranges[j].start);
	printf("dim:%u,start:%lf,end:%lf\n",dim,ranges[0].start,ranges[0].end);
	v=malloc(dim*sizeof(double));
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<dim;j++)
			v[j]=(double)rand()/RAND_MAX*(ranges[j].end-ranges[j].start)+ranges[j].start;
		sum+=fun(dim,v);
	}
	for(int j=0;j<dim;j++) printf("%lf%c",v[j],j==4?'\n':' ');
	printf("aLOMOST\n");
	return sum/SIZE*vol;
}


int main(int argc, const char* argv[]){
	RANGE range=(RANGE){0.0,1.0};
	printf("I1:%.19lf\n",MonteCarloInt(1,&range,fun1));
	RANGE* ranges;
	ranges=malloc(5*sizeof(RANGE));
	ranges[0]=(RANGE){0.0,0.7};
	ranges[1]=(RANGE){0.0,0.8};
	ranges[2]=(RANGE){0.0,0.9};
	ranges[3]=(RANGE){0.0,1.0};
	ranges[4]=(RANGE){0.0,1.1};
	printf("I2:%.19lf\n",MonteCarloInt(5,ranges,fun2));
	return 0;
}
