#include "statlib.h"

int mean(double* v, unsigned long size, double* result){
	if(size==0||result==NULL) {printf("Mean:Input Error!\n"); exit(0);}
	unsigned long remainder=size%BUFFERSIZE;
	unsigned long ntimes=size/BUFFERSIZE;
	printf("Ntimes:%zu,Remainder:%zu\n",ntimes,remainder);
	double* resultarray=malloc(sizeof(*resultarray)*(ntimes+1));
	if(!resultarray) {printf("Malloc Error!\n"); exit(0);}
	
	for(int i=0; i<ntimes+1; i++){
		unsigned long length=(i==ntimes)?remainder:BUFFERSIZE;
		double* buffer=malloc((length+1)*sizeof(double));
		if(!buffer) {printf("Malloc Error!\n"); exit(0);}
		memcpy(buffer+1,v+i*BUFFERSIZE,length*sizeof(double));
		doubleSort(buffer,1,length);
	
		resultarray[i]=0;
		for(int j=0; j<length; j++)
			resultarray[i]+=buffer[j+1];
		*result+=resultarray[i];
		free(buffer);
	}
	printf("Advanced Mu:%lf\n",*result);
	*result=*result/size;
	free(resultarray);
	return 1;
}
	

int momentum(double* v, unsigned long size, int k, double* result){
	if(size==0||result==NULL) {printf("Mean:Input Error!\n"); exit(0);}
	double pr=0,nr=0;
	double mu;
	mean(v,size,&mu);
	printf("Mu:%lf\n",mu);
	unsigned long remainder=size%BUFFERSIZE;
	unsigned long ntimes=size/BUFFERSIZE;
	double* resultarray=malloc(2*sizeof(*resultarray)*(ntimes+1));
	if(!resultarray) {printf("Malloc Error!\n"); exit(0);}
	
	for(int i=0; i<ntimes+1; i++){
		unsigned long length=(i==ntimes)?remainder:BUFFERSIZE;
		double* buffer=malloc((length+1)*sizeof(double));
		if(!buffer) {printf("Malloc Error!\n"); exit(0);}
		for(int j=0; j<length; j++)
			buffer[j+1]=v[j+i*BUFFERSIZE]-mu;
		doubleSort(buffer,1,length);
		
		int m;
		for(m=0; m<length; m++)
			if(buffer[m+1]>0) break;	
		for(int j=m; j<length; j++)
			resultarray[2*i]+=pow(buffer[j+1],k);
		pr+=resultarray[2*i];
		for(int j=m; j>=0; j--)
			resultarray[2*i+1]+=pow(buffer[j+1],k);
		nr+=resultarray[2*i+1];
		free(buffer);
	}
	*result=(pr+nr)/size;
	free(resultarray);
	return 1;
}
