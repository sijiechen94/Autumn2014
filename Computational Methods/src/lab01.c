#include "stdio.h"
#include "stdlib.h"

#define ARRAYSIZE 41

//To reduce error to below 1e-6, first 0x100000(1048576) terms are summed,
//so that, the error is less than 1/0x100000, since 1/k/(k+x) is less than k^-2,
//which gives a summation of approximately 1e-6 adding from the 1e6th term to infinite
#define LASTTERM 0x100000

int main(){
	double v[2*ARRAYSIZE];
	FILE* fp=fopen("output/lab01","w");
	if(!fp){ printf("Fopen Error!\n"); exit(-1);}

	for(int i=0;i<ARRAYSIZE;i++){
		v[2*i]=i<11?i/10.0:(i-10)*10.0;
		v[2*i+1]=0;
		for(int k=1;k<LASTTERM;k++)
			v[2*i+1]+=1.0/k/(k+v[2*i]);
	}

	fwrite(v,sizeof(double),2*ARRAYSIZE,fp);
	return 0;
}
