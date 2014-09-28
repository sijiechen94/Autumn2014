#include "1.h"
#include "stdio.h"
#include "statlib.h"

int main(){
	int seed=3;
	FILE *output=fopen("./output/1.output","w");
	double* vector;
	vector=malloc(100000000*sizeof(double));
	if(!vector){printf("Malloc Error\n!"); exit(0);}
	for(int i=0; i<100000000; i++){
		vector[i]=(double)seed/(unsigned long)0x80000000;
		seed=schrage(seed);
	}
	double momentum2=0;
	momentum(vector,100000000,3,&momentum2);
	printf("2th momentum:%lf\n",momentum2);
	double s=0;
	for(int i=0;i<100000000;i++) s+=vector[i];
	printf("Simple Mu:%lf\n",s);
	return 0;
}
