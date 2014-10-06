#include "1.h"
#include "stdio.h"
#include "stdlib.h"

#define SIZE 10000000
#define SEED 3

//Some main program to invoke Schrage and do I/O
int main(){

	FILE *output=fopen("schrage.binary","w");
	if(!output){printf("Fopen Error\n!"); exit(0);}
	double* vector;

	//Maximum memory usage and shortest running time here.
	//If SIZE is too large for a single malloc,
	//use some appropriate buffer size for your machine, like 1MB,
	//will give you overall best performance.
	vector=malloc(SIZE*sizeof(double));
	if(!vector){printf("Malloc Error\n!"); exit(0);}

	sschrage(SEED);
	for(int i=0; i<SIZE; i++)
		vector[i]=schrage();
	fwrite(vector,sizeof(double),SIZE,output);

	return 0;
}
