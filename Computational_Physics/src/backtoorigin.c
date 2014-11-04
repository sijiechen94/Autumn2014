#include <stdlib.h>
#include <stdio.h>
#include <string.h>			//For memset
#include <unistd.h>			//In case it might be running parallelly
#include <sys/types.h>			//, include these two headers for prototypes like fork() and getpid();

#define RAND() (double)rand()/RAND_MAX
#define MAX_LENGTH 1048576		//Each particle walks no more than this # of steps
#define SIZE 65536			//This is # of particles for each dimension
#define DIM 3				//Highest dimension

int rw1d(int* pos){
	if(RAND()>0.5) *pos+=1;
	else *pos-=1;
	return *pos;			//Returns 0 only if returns to origin
}

int rw2d(int* pos){
	double u=RAND();
	if(u>0.5){
		if(u>0.75) pos[0]+=1;
		else pos[0]-=1;
	}else{
		if(u>0.25) pos[1]+=1;
		else pos[1]-=1;
	}				//Four directions allowed
	return pos[0]||pos[1];		//Returns 0 only if returns to origin
}

int rw3d(int* pos){
	double u=6*RAND();
	if(u>5) 	pos[0]+=1;
	else if(u>4)	pos[0]-=1;
	else if(u>3)	pos[1]+=1;
	else if(u>2)	pos[1]-=1;
	else if(u>1)	pos[2]+=1;
	else		pos[2]-=1;	//Six directions allowed
	return pos[0]||pos[1]||pos[2];	//Returns 0 only if returns to origin
}

/*  For each dimension, take each particle to make random walks
 *  , and record their first step returning to origin
 */
int backtoorigin(int dim, int size, int* result){

	//Array of pointers to functions
	int (*rwfun[3])(int*)={rw1d,rw2d,rw3d};

	for(int i=0;i<size;i++){
		
		//Allocate an array for coordinates
		int* p;
		p=malloc(dim*sizeof(int));
		if(!p){fprintf(stderr,"MALLOC ERROR!\n");exit(0);}
		memset(p,0,dim*sizeof(int));

		//Prepare to get 0 return value, and record their steps walked
		int rv=-1;
		int j;
		for(j=0;j<MAX_LENGTH;j++){
			rv=rwfun[dim-1](p);
			if(!rv) break;
		}
		result[i]=j!=1048576?j+1:j-1;	//Last step does not matter since it hardly possible
						//Otherwise there might be a segment fault due to oversized offset
	}
	return 0;
}

/*   For each dimension, sum # of particles ended on same step
 *   , and do a cumulative sum
 */
void transform(int* result, int* output){
	
	//Initialize and transform
	memset(output,0,MAX_LENGTH*sizeof(int));
	for(int i=0;i<SIZE;i++)
		(*(output+result[i]))++;

	//Accumulate
	for(int i=1;i<MAX_LENGTH;i++)
		*(output+i)+=*(output+i-1);
}

int main(int argc,const char* argv[]){

	char filename[16]="backtoorigin";
	
	/*  This is intended to be running on n04
	 *  do not uncomment this unless you are running this parallel
	 *  
	 *  for(int i=0;i<5;i++) fork();
	 *  pid_t mypid;
	 *  mypid=getpid();
	 *  sprintf(filename,"%d",mypid);
	 *
	 */

	//Initialization
	int *result, *output;
	result=malloc(SIZE*sizeof(int));
	output=malloc(MAX_LENGTH*sizeof(int));
	if(!result||!output){fprintf(stderr,"MALLOC ERROR!\n");exit(0);}
	FILE *fp;
	if(!(fp=fopen("backtoorigin","w"))){fprintf(stderr,"FOPEN ERROR!\n");exit(0);}

	//Main loop
	for(int i=1;i<=DIM;i++){
		backtoorigin(i,SIZE,result);
		transform(result,output);
		 fwrite(output,sizeof(int),MAX_LENGTH,fp);
	}

	return 0;
}
