/*  direct.c
 *
 *  Direct method for Assignment 5
 *  Use redirection to I/O
 */

#include "discreteARM.h"

#define SIZE 0x1000000

int main(int argc, const char* argv[]){
	POINTS data;
	makecmf(&data,stdin);
	double* vector;
        vector=malloc(SIZE*sizeof(double));
        if(!vector) {printf("MALLOC ERROR!\n"); exit(0);}
	for(int i=0; i<SIZE; i++)
		vector[i]=data.x[searchIndex(data,foo4random())];
	fwrite(vector,sizeof(double),SIZE,stdout);
	return 0;
}//Quite simple, check discreteARM.c for details
