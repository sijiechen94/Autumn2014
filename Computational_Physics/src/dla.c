#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <float.h>

#ifdef _POSIX_THREADS
#define PTHREAD_SUPPORT 1
#include <pthread.h>
#endif
#ifndef _POSIX_THREADS
#define PTHREAD_SUPPORT 0
#endif

#ifndef N_THREADS
#define N_THREADS 32
#endif

#define malloccheck(ptr) {if(!ptr) {fprintf(stderr,"MALLOC ERROR!\n"); exit(0);}}

typedef struct{
	char* map;
	int* birth_range;
}arg_t;

typedef struct{
	int x;
	int y;
}coor;
#define N_SIZE 20000
#define MAP_SIZE 2049
#define C2O(x) ((x)+(MAP_SIZE-1)/2)
#define O2C(x) ((x)-(MAP_SIZE-1)/2)

int workdone;
int Npart; 
int maxrange;


int getrange(coor pos){
	int x,y;
	x=abs(O2C(pos.x));
	y=abs(O2C(pos.y));
	return x+y;
}

int toofar(coor cur_pos, coor init_pos){
	if((getrange(cur_pos)-getrange(init_pos))>10) return 1;
	else return 0;
}

void walk_a_step(coor* pos){
	pthread_t tid;
	tid=pthread_self();
	int rr=rand();
	double u=(double)rr/RAND_MAX;
	int x=pos->x;
	int y=pos->y;
	
	if(u>0.5){
		if(u>0.75) pos->x=x+1;
		else pos->x=x-1;
	}else{
		if(u>0.25) pos->y=y+1;
		else pos->y=y-1;
	}
}

int stick(coor cur_pos, char* map){
	int x=cur_pos.x;
	int y=cur_pos.y;
	if(*(map+MAP_SIZE*x+y-1)||
	   *(map+MAP_SIZE*x+y+1)||
	   *(map+MAP_SIZE*(x+1)+y)||
	   *(map+MAP_SIZE*(x-1)+y)) return 1;
	else return 0;
}

void create_particle(coor* output, int* range){
	pthread_t tid;
	tid=pthread_self();
	int rr=rand_r((unsigned*)&tid)%(8**range);
	int x,y;

	if(rr<2**range){
		x=*range;
		y=rr-*range;
	}else if(rr<4**range){
		x=3**range-rr;
		y=*range;
	}else if(rr<6**range){
		x=-*range;
		y=5**range-rr;
	}else{
		x=rr-7**range;
		y=-*range;
	}

	output->x=C2O(x);
	output->y=C2O(y);
}

int random_walk(coor* init_pos, char* map){

	coor *pos;
	pos=malloc(sizeof(*pos));
	malloccheck(pos);
	memcpy(pos,init_pos,sizeof(*pos));
	while(!stick(*pos,map)){
		walk_a_step(pos);
		if(toofar(*pos,*init_pos))
			return 0;
	}
	*init_pos=*pos;
	free(pos);
	return 1;
}

void addpart(coor part, char* map){
	*(map+MAP_SIZE*part.x+part.y)=1;
	int r=getrange(part);
	maxrange=r>maxrange?r:maxrange;
}

void worker_work(arg_t* work){

	int localdone=0;
	coor *pos;
	pos=malloc(sizeof(*pos));
	malloccheck(pos);
	while(!localdone){
		create_particle(pos,work->birth_range);
		localdone=random_walk(pos,work->map);
	}
	addpart(*pos,work->map);
	free(pos);
}

int get_birth_range(int n, int mapsize){
	return maxrange+10>MAP_SIZE/2-1?MAP_SIZE/2-1:maxrange+10;
}

void* worker_start(void* arg){
	
	while(!workdone){
		*(((arg_t*)arg)->birth_range)=get_birth_range(Npart,MAP_SIZE);
		//if(!Npart%100)
		fprintf(stderr,"Npart:%d\n",Npart);
		worker_work((arg_t*)arg);
		if(++Npart==N_SIZE) workdone=1;
	}

	fprintf(stderr,"Particle Number: %d\n",Npart);
	pthread_exit(NULL);
	return (void*)0;
}

void output_map(char* map){
	for(int i=0;i<MAP_SIZE;i++){
		for(int j=0;j<MAP_SIZE;j++){
			fprintf(stderr,"%c",*(map+i*MAP_SIZE+j)?'W':'-');
		}
		fprintf(stderr,"\n");
	}
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

	//Initialize arg	
	arg_t arg;
	arg.map=malloc(MAP_SIZE*MAP_SIZE*sizeof(char));
	malloccheck(arg.map);
	memset(arg.map,0,MAP_SIZE*MAP_SIZE);
	memset(arg.map+((MAP_SIZE-1)/2)*MAP_SIZE+(MAP_SIZE-1)/2,1,1);
	arg.birth_range=malloc(sizeof(int));
	malloccheck(arg.birth_range);
	fprintf(stderr,"Arg prepared!\n");

	//Create threads
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_t *tid_list;
	tid_list=malloc((N_THREADS-1)*sizeof(pthread_t));
	malloccheck(tid_list);
	workdone=0;
	Npart=1;
	int err=0;
	fprintf(stderr,"Ready to call threads!\n");
	for(int i=1;i<N_THREADS;i++){
		err=pthread_create(&(tid_list[i-1]),&attr,worker_start,(void*)&arg);
		if(err!=0){
			fprintf(stderr,"Failed to create thread: %s\n",strerror(err));
			exit(0);
		}
	}
	fprintf(stderr,"\t\t\tCreated threads!\n");
	sleep(20);
	for(int i=1;i<N_THREADS;i++){
		pthread_cancel(tid_list[i-1]);
	}
	
	
	//output_map(arg.map);
	return 0;
}
