#include <stdio.h>
#include <stdlib.h>
#include <math.h>			//For sin
#include <unistd.h>			//In case it involves parallel
#include <string.h>			//For strcat

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795028841971693993751058
#endif
#define inf 1.0/0.0
//Following two constants varies between each run
//Do NOT set frequency to pi and scaling factor to inf, it will cause nan
#define ANGULAR_FREQUENCY 1e-6		//Omega in the problem
#define SCALING_FACTOR 0.5		//Works like the field E
#define POINTS_PER_PROCESS 1024		//Particles handled by each process
#define TIME_PER_ENTRY 1024		//Interval of Snaps
#define TOTAL_TIME 16384		//Total time each particle moves
#define RAND() (double)rand()/RAND_MAX

double externalForce(int time){
	return SCALING_FACTOR*sin(ANGULAR_FREQUENCY*time);
}

int randomWalkSin(int pos, int time){
	double u=RAND();
	if (u>(0.5+externalForce(time)))
		return pos+1;
	else return pos-1;
}
	

int main(int argc, const char* argv[]){

	//Output preparation
	char filename[40];
	sprintf(filename,"w=%lf_a=%lf_figure",ANGULAR_FREQUENCY,SCALING_FACTOR);
	FILE* figurefile=fopen(filename,"w");
	sprintf(filename,"w=%lf_a=%lf_data",ANGULAR_FREQUENCY,SCALING_FACTOR);
	FILE* datafile=fopen(filename,"w");
	if(!figurefile||!datafile) {fprintf(stderr,"FOPEN ERROR!\n"); exit(0);}

	//Memory allocation
	int *figure=NULL,*data=NULL;
	figure=malloc(TOTAL_TIME*sizeof(int));
	data=malloc((TOTAL_TIME/TIME_PER_ENTRY-1)*sizeof(int));
	if(!figure||!datafile) {fprintf(stderr,"MALLOC ERROR!\n"); exit(0);}

	//Main loop
	for(int particle=0;particle<POINTS_PER_PROCESS;particle++){
		int pos=0;		
		for(int time=0;time<TOTAL_TIME;time++){
			pos=randomWalkSin(pos,time);
			figure[time]=pos;
			if(time&&!(time%TIME_PER_ENTRY))
				data[time/TIME_PER_ENTRY-1]=pos;
		}
		fwrite(figure,sizeof(int),TOTAL_TIME,figurefile);
		fwrite(data,sizeof(int),TOTAL_TIME/TIME_PER_ENTRY-1,datafile);
	}
	return 0;
}
