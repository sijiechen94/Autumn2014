#include "stdio.h"
#include "stdlib.h"

#define ARRAYSIZE 41
#define LASTTERM 0x100000
int main(){
	double* v=malloc(sizeof(*v)*ARRAYSIZE*41);
	FILE* fp=fopen("output/lab01","w");
	if(fp!=NULL){
		for(int i=0;i<ARRAYSIZE;i++){
			*(v+2*i)=i<11?i/10.0:(i-10)*10.0;
			*(v+2*i+1)=0;
			for(int k=1;k<LASTTERM;k++)
				*(v+2*i+1)+=1.0/k/(k+*(v+2*i));
		}
		fwrite(v,sizeof(double),2*ARRAYSIZE,fp);
	}
	free(v);
	fclose(fp);
	return 0;
}
