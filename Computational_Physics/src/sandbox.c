#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAP_SIZE 4095
#define OUTPUTNAME "sandbox.dat"

void usage(){
	
	fprintf(stderr,"Usage:\tSecond argument as input file\n");
	exit(0);
}

int sandbox(char* map, int* output){

	for(int i=1;i<=MAP_SIZE/2;i++){
		int n=0;
		for(int j=-i;j<=i;j++){
			for(int k=-i;k<=i;k++){
				if (*(map+(MAP_SIZE/2+j)*MAP_SIZE+(MAP_SIZE/2+k))) n++;
			}
		}
		if(n<0) return -1;
		output[i-1]=n;
	}

	return 0;
}

int main(int argc, const char* argv[]){
	
	if(argc!=2) usage();

	FILE* fp;
	FILE* fp2;
	if(!(fp=fopen(argv[1],"r"))){fprintf(stderr,"Fopen failed! %s:%s\n",argv[1],strerror(errno));exit(0);}
	if(!(fp2=fopen(OUTPUTNAME,"w"))){fprintf(stderr,"Fopen failed! %s:%s\n",OUTPUTNAME,strerror(errno));exit(0);}

	fprintf(stderr,"Reading %d*%d input file\nWarning: This is n^3 algorithm, so it may take some time.\n",MAP_SIZE,MAP_SIZE);

	char* map;
	if(!(map=malloc(MAP_SIZE*MAP_SIZE))){fprintf(stderr,"Malloc failed!\n");exit(0);}
	if(fread(map,1,MAP_SIZE*MAP_SIZE,fp)<MAP_SIZE*MAP_SIZE){fprintf(stderr,"Fread error:%s\n",strerror(errno));exit(0);}

	int* result;
	if(!(result=malloc(MAP_SIZE/2*sizeof(int)))){fprintf(stderr,"Malloc failed!\n");exit(0);}

	if(sandbox(map,result)!=0){fprintf(stderr,"Oops, something bad happened...\n");exit(0);}
	else{
		if(fwrite(result,sizeof(int),MAP_SIZE/2,fp2)!=MAP_SIZE/2)
			fprintf(stderr,"Fwrite error:%s\n",strerror(errno));
		else fprintf(stderr,"Result wrote to %s, size:%d\n",OUTPUTNAME,MAP_SIZE/2);
	}
	return 0;
}
	
