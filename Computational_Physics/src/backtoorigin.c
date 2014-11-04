#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RAND() (double)rand()/RAND_MAX
#define MAX_LENGTH 65535
#define SIZE 65536

int rw1d(int* pos){
	if(RAND()>0.5) *pos+=1;
	else *pos-=1;
	return *pos;
}

int rw2d(int* pos){
	double u=RAND();
	if(u>0.5){
		if(u>0.75) pos[0]+=1;
		else pos[0]-=1;
	}else{
		if(u>0.25) pos[1]+=1;
		else pos[1]-=1;
	}
	return pos[0]||pos[1];
}

int rw3d(int* pos){
	double u=6*RAND();
	if(u>5) 	pos[0]+=1;
	else if(u>4)	pos[0]-=1;
	else if(u>3)	pos[1]+=1;
	else if(u>2)	pos[1]-=1;
	else if(u>1)	pos[2]+=1;
	else		pos[2]-=1;
	return pos[0]||pos[1]||pos[2];
}

int backtoorigin(int dim, int size, int* result){
	int (*rwfun[3])(int*)={rw1d,rw2d,rw3d};
	for(int i=0;i<size;i++){
		int* p;
		p=malloc(dim*sizeof(int));
		if(!p){fprintf(stderr,"MALLOC ERROR!\n");exit(0);}
		memset(p,0,dim*sizeof(int));
		int rv=-1;
		int j;
		for(j=0;j<MAX_LENGTH;j++){
			rv=rwfun[dim-1](p);
			if(!rv) break;
		}
		result[i]=j+1;
	}
	printf("back!\n");
	return 0;
}

int main(int argc,const char* argv[]){

	int *result;
	result=malloc(SIZE*sizeof(int));
	if(!result){fprintf(stderr,"MALLOC ERROR!\n");exit(0);}
	FILE *fp;
	if(!(fp=fopen("backtoorigin","w"))){fprintf(stderr,"FOPEN ERROR!\n");exit(0);}

	for(int i=1;i<4;i++){
		backtoorigin(i,SIZE,result);
		fwrite(result,sizeof(int),SIZE,fp);
	}
	return 0;
}
