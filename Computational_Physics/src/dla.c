#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <float.h>

#ifdef _POSIX_THREADS			//Test macros, you may still have to use -pthread at compiling time
#define PTHREAD_SUPPORT 1		//depending on platforms, although it's SUSv2
#include <pthread.h>
#endif
#ifndef _POSIX_THREADS
#define PTHREAD_SUPPORT 0
#endif

#ifndef N_THREADS			//Compiler defined macro recommended
#define N_THREADS 32			//Pthreads to be invoked at one time
#endif
#define N_SIZE 200000			//Target particle number
#define MAP_SIZE 4095			//Size of square lattice
#define BONUS_RANGE 100			//Range outside current pattern at which new particles are created
					//Also range which a particle is expelled once goes beyond it
#define HALF_CORE 0			//Core radius, 0 means 1*1, 1 means 3*3. Modification not recommended
#define C2O(x) ((x)+(MAP_SIZE-1)/2)	//Coordinates transformation, center -> origin
#define O2C(x) ((x)-(MAP_SIZE-1)/2)	//Coordinates transformation, origin -> center

#define malloccheck(ptr) {if(!ptr) {fprintf(stderr,"MALLOC ERROR!\n"); exit(0);}}

typedef struct{
	char* map;
	int* birth_range;
}arg_t;

typedef struct{
	int x;
	int y;
}coor_t;

pthread_t *tid_list;
int workdone;
int Npart; 				//Current number of particle of the pattern
int maxrange;				//Maximum distance of a particle of the pattern from center
unsigned tseed=1;			//Global seed used by rand_r

arg_t arg;

int getrange(coor_t pos){
	return (int)floor(sqrt(pow(O2C(pos.x),2)+pow(O2C(pos.y),2)));
}

int toofar(coor_t cur_pos, coor_t init_pos){
	if((getrange(cur_pos)-getrange(init_pos))>BONUS_RANGE) return 1;
	if(cur_pos.x==MAP_SIZE-1||cur_pos.x==1) return 1;
	if(cur_pos.y==MAP_SIZE-1||cur_pos.y==1) return 1;
	else return 0;
}

//Walk in four directions
void walk_a_step(coor_t* pos){
	double u=(double)rand_r((unsigned*)&tseed)/RAND_MAX;
	
	if(u>0.5){
		if(u>0.75) pos->x=pos->x+1;
		else pos->x=pos->x-1;
	}else{
		if(u>0.25) pos->y=pos->y+1;
		else pos->y=pos->y-1;
	}
}

//Check for four directions
int stick(coor_t cur_pos, char* map){
	int x=cur_pos.x;
	int y=cur_pos.y;
	if(*(map+MAP_SIZE*x+y-1)||
	   *(map+MAP_SIZE*x+y+1)||
	   *(map+MAP_SIZE*(x+1)+y)||
	   *(map+MAP_SIZE*(x-1)+y)){ 
		 return 1;
	}
	else return 0;
}

//Create a particle at given range, new coordinates as output parameter
void create_particle(coor_t* output, int* range){
	int rr=rand_r((unsigned*)&tseed);
	int x,y;

//  2-Norm generating
	double u=(double)rr/RAND_MAX*2*M_PI;
	x=(int)(lround(cos(u)**range));	
	y=(int)(lround(sin(u)**range));	

	output->x=C2O(x);
	output->y=C2O(y);
	//fprintf(stderr,"Created a particle at x:%d, y:%d!\n",output->x,output->y);
}


//The whole random walk process
int random_walk(coor_t* init_pos, char* map){

	coor_t *pos;
	pos=malloc(sizeof(*pos));
	malloccheck(pos);
	memcpy(pos,init_pos,sizeof(*pos));
	while(!stick(*pos,map)){
		walk_a_step(pos);
		if(toofar(*pos,*init_pos)){
			free(pos);
			return 0;
		}
	}
	*init_pos=*pos;
	free(pos);
	return 1;
}


void addpart(coor_t part, char* map){
	//fprintf(stderr,"Adding some particle!X:%dY:%d\n",part.x,part.y);
	*(map+MAP_SIZE*part.x+part.y)=1;
	int r=getrange(part);
	maxrange=r>maxrange?r:maxrange;			//Modify maxrange if needed
	//fprintf(stderr,"Added a particle!\n");
}

int get_birth_range(){
	if((maxrange+BONUS_RANGE+2)>(MAP_SIZE/2)){fprintf(stderr,"Error:Particle is reaching boundary!\nNpart:%d\n",Npart);exit(0);}
	return maxrange+BONUS_RANGE;			//Currently there is a bug with this exit,
							//Many threads may call exit within limited time
							//So functions registered at atexit may have insufficient time to finish
							//Do not use this line by limit N_SIZE
}


//Thread function
void* worker_work(void* arg){
	//fprintf(stderr,"Worker start to work!\n");
	int localdone=0;
	coor_t *pos;
	pos=malloc(sizeof(*pos));
	malloccheck(pos);
	while(!localdone){
		*(((arg_t*)(arg))->birth_range)=get_birth_range();
		create_particle(pos,((arg_t*)(arg))->birth_range);
		localdone=random_walk(pos,((arg_t*)(arg))->map);
	}
	//fprintf(stderr,"Finished a piece at x:%d, y:%d!\n",pos->x,pos->y);
	return pos;
}


//Output snapshots with continous filenames
void output(){
	static int filenum=0;
	char filename[10];
	sprintf(filename,"map%d.bmp",filenum++);		
	fprintf(stderr,"Finished! Npart:%d\n",Npart);
	FILE *fp;
	fp=fopen(filename,"w");
	fwrite(arg.map,1,MAP_SIZE*MAP_SIZE,fp);
	fclose(fp);
}	

int main(int argc, const char* argv[]){

	if(!PTHREAD_SUPPORT){
		fprintf(stderr,"Pthread not support! Abort!\n");
		exit(0);
	}else if(N_THREADS<2){
		fprintf(stderr,"Too few threads! At least 2 threads! Abort!\n");
		exit(0);
	}else if(N_THREADS>128){
		fprintf(stderr,"Warning: Too much (%d) threads!\n",N_THREADS);
	}else {
		fprintf(stderr,"This program use POSIX thread model!\n");
		fprintf(stderr,"It is using %d threads!\n",N_THREADS);
	}
	
	//Register atexit for multiple ways of exit
	if(atexit(output)!=0)fprintf(stderr,"Failed to register output function to atexit!\n");
	
	//Initialize arg	
	arg.map=malloc(MAP_SIZE*MAP_SIZE*sizeof(char));
	malloccheck(arg.map);
	memset(arg.map,0,MAP_SIZE*MAP_SIZE);
	for(int i=-HALF_CORE;i<=HALF_CORE;i++)
		memset(arg.map+(((MAP_SIZE-1)/2)-i)*MAP_SIZE+(MAP_SIZE-1)/2-HALF_CORE,1,2*HALF_CORE+1);
	arg.birth_range=malloc(sizeof(int));
	malloccheck(arg.birth_range);

	//Create threads
	pthread_t *tid_list;
	tid_list=malloc((N_THREADS-1)*sizeof(pthread_t));
	malloccheck(tid_list);
	workdone=0;
	Npart=1;
	maxrange=BONUS_RANGE;
	int err=0;
	//fprintf(stderr,"Ready to call threads!\n");
	coor_t *pos;
	pos=malloc(sizeof(*pos));
	malloccheck(pos);
	while(!workdone){
		for(int i=1;i<N_THREADS;i++){
			err=pthread_create(&(tid_list[i-1]),NULL,worker_work,(void*)&arg);
			if(err!=0){ fprintf(stderr,"Failed to create thread: %s\n",strerror(err)); exit(0); }
		}
		for(int i=1;i<N_THREADS;i++){
			pthread_join(tid_list[i-1],(void**)&pos);
			pthread_kill(tid_list[i-1],SIGINT);
			if(!(Npart%(N_SIZE/10))) output();
			Npart++;if(Npart==N_SIZE)workdone=1;
			addpart(*pos,arg.map);
		}
	}
	output();

	return 0;
}

