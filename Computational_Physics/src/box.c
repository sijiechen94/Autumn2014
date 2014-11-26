#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAP_SIZE 4095
#define OUTPUTNAME "box.dat"

typedef struct{
	int mapsize;
	int *epsilon;
	int length;
	/* Obsoleted
	int newsize;
	*/
}box_plan_t;

//Plan execuation
int box_exec(char* input, int* output, box_plan_t *plan){

	for(int i=0;i<plan->length;i++){

		//For each boxsize
		int occupied=0;
		int blocksize=plan->epsilon[i];
		int count=0;

		for(int j=0;j<plan->mapsize/blocksize;j++){
			for(int k=0;k<plan->mapsize/blocksize;k++){
				
				//For each box
				count++;
				int n=0;
				for(int jj=0;jj<blocksize;jj++){
					for(int kk=0;kk<blocksize;kk++){
						if (*(input+(blocksize*j)*plan->mapsize+(blocksize*k)+jj*plan->mapsize+kk)) {n=1;break;}
					}
					if(n==1) break;
				}
				if(n==1) occupied++;

			}
		}

		output[i]=occupied;
		fprintf(stderr,"Blocksize:%d,Blockcount:%d,Occupied:%d\n",blocksize,count,occupied);
	}

	for(int i=0;i<plan->length;i++){
		output[plan->length+i]=plan->epsilon[i];
	}

	/* Obsoleted by new mathod
	char* newmap;
	if(!(newmap=malloc(plan->newsize*plan->newsize))){fprintf(stderr,"Malloc error!\n");exit(0);}

	//Initialize newmap
	for(int i=0;i<plan->oldsize;i++){
		memcpy(newmap+plan->newsize*i,input+plan->oldsize*i,plan->oldsize);
		memset(newmap+plan->newsize*i+plan->oldsize,0,plan->newsize-plan->oldsize);
	}
	fprintf(stderr,"New map inited! Size:%d\n",plan->newsize);

	for(int i=0;i<plan->length;i++){
		int occupied=0;
		int blocksize=1<<i;
		int count=0;
		for(int j=0;j<1<<(plan->length-i);j++){
			for(int k=0;k<1<<(plan->length-i);k++){
				count++;
				int n=0;
				for(int jj=0;jj<blocksize;jj++){
					for(int kk=0;kk<blocksize;kk++){
						if (*(newmap+(blocksize*j)*plan->newsize+(blocksize*k)+jj*plan->newsize+kk)) {n=1;break;}
					}
					if(n==1) break;
				}
				if(n==1) occupied++;
			}
		}
		output[i]=occupied;
		fprintf(stderr,"Blocksize:%d,Blockcount:%d,Occupied:%d\n",blocksize,count,occupied);
	}
	*///But may be reused

	return 0;
}

//Create a plan, currently using new method only
int box_create_plan(int mapsize, box_plan_t* outplan){
	
	if(mapsize<0) return -1;

	int *buffer;
	if(!(buffer=malloc(mapsize*sizeof(int)))){fprintf(stderr,"Malloc error at box_create_plan!\n");exit(0);}

	int length=0;
	for(int i=1;i<mapsize;i++){
		if(mapsize%i==0)
			buffer[length++]=i;
	}
	
	if(!(outplan->epsilon=malloc(length*sizeof(int)))){fprintf(stderr,"Malloc error at box_create_plan!\n");exit(0);}
	memcpy(outplan->epsilon,buffer,sizeof(int)*length);
	outplan->length=length;
	outplan->mapsize=mapsize;

	/* Obsoleted by new method
	int MAXEXP=sizeof(int)*8-2;
	int q=mapsize;
	int i=1;
	for(;i<=MAXEXP;i++){
		q=q/2;
		if(!q) break;
	}
	if(q!=0) return -1;
	outplan->oldsize=mapsize;
	outplan->length=i;
	outplan->newsize=1<<i;
	fprintf(stderr,"oldsize:%d,length:%d,newsize:%d\n",outplan->oldsize,outplan->length,outplan->newsize);
	*///But may be reused

	free(buffer);	
	return 0;
}

//Output array should be allocated according to output parameter of this API
int box_getsize(box_plan_t *plan, int* output){
	if(output){*output=2*plan->length;return 0;}
	return -1;
}











void usage(){
	
	fprintf(stderr,"Usage:\tSecond argument as input file\n");
	exit(0);
}

int main(int argc, const char* argv[]){
	
	if(argc!=2) usage();

	FILE* fp;
	FILE* fp2;
	box_plan_t plan;
	int result_size;
	int* result;

	if(!(fp=fopen(argv[1],"r"))){fprintf(stderr,"Fopen failed! %s:%s\n",argv[1],strerror(errno));exit(0);}
	if(!(fp2=fopen(OUTPUTNAME,"w"))){fprintf(stderr,"Fopen failed! %s:%s\n",OUTPUTNAME,strerror(errno));exit(0);}

	fprintf(stderr,"Reading %d*%d input file\nWarning: This is n^3 algorithm, so it may take some time.\n",MAP_SIZE,MAP_SIZE);

	char* map;
	if(!(map=malloc(MAP_SIZE*MAP_SIZE))){fprintf(stderr,"Malloc failed!\n");exit(0);}
	if(fread(map,1,MAP_SIZE*MAP_SIZE,fp)<MAP_SIZE*MAP_SIZE){fprintf(stderr,"Fread error:%s\n",strerror(errno));exit(0);}

	if(box_create_plan(MAP_SIZE,&plan)!=0){fprintf(stderr,"box_create_plan error!\n");exit(0);}

	if((box_getsize(&plan,&result_size)!=0)){fprintf(stderr,"box_getsize error!\n");exit(0);}
	if(!(result=malloc(result_size*sizeof(int)))){fprintf(stderr,"Malloc failed!\n");exit(0);}

	if(box_exec(map,result,&plan)!=0){fprintf(stderr,"Oops, something bad happened...\n");exit(0);}
	else{
		if(fwrite(result,sizeof(int),result_size,fp2)!=result_size)
			fprintf(stderr,"Fwrite error:%s\n",strerror(errno));
		else fprintf(stderr,"Result wrote to %s, size:%d\n",OUTPUTNAME,result_size);
	}
	return 0;
}
	
