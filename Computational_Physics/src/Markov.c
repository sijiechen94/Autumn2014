#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define RAND() ((double)rand()/RAND_MAX)

#define FILENAME "markov.chain"

#define SIGMA_X 1
#define SIGMA_Y 2
#define SIZE_OF_VARIABLES 2
#define TOTAL_TIME 1048576				//This naive algorithm is O(t) and Memory-limited
							//However, just by fwrite more frequently it is no more memory-limited
							//Since only two states need to be kept at the same time
#define DELTA 4
#define INITIAL_VALUE -15

double Hamiltonian(double* Xs, int length){
	double x=Xs[0];
	double y=Xs[1];
	return ((x)*(x)/(2*SIGMA_X*SIGMA_X)+(y)*(y)/(2*SIGMA_Y*SIGMA_Y));
}

double transition_rate(double H_old, double H_new){
	return H_new<H_old ? 1 : (exp(H_old-H_new));
}

void initial_condition(double* chain){
	for(int i=0;i<SIZE_OF_VARIABLES;i++){
		*(chain+i*TOTAL_TIME)=INITIAL_VALUE;	//Same initial values applied to all variables, does not matter
	}
}

double new_value_of(double old){
	return old+(RAND()-0.5)*DELTA;			//Walk a step
}

void time_evolution(double* chain){

	double H0,H1;	
	double *XX;
	if(!(XX=malloc(sizeof(*XX)*SIZE_OF_VARIABLES))){fprintf(stderr,"Malloc error in time_evolution!\n");exit(0);}
	for(int j=0;j<SIZE_OF_VARIABLES;j++){
		XX[j]=*(chain+j*TOTAL_TIME);
	}						//Load initial condition
	H0=Hamiltonian(XX,SIZE_OF_VARIABLES);	
	for(int i=1;i<TOTAL_TIME;i++){
		for(int j=0;j<SIZE_OF_VARIABLES;j++){
			XX[j]=new_value_of(*(chain+(i-1)+j*TOTAL_TIME));
		}
		H1=Hamiltonian(XX,SIZE_OF_VARIABLES);
		if(RAND()<transition_rate(H0,H1)){	//If success, renew H and record the step
			H0=H1;
			for(int j=0;j<SIZE_OF_VARIABLES;j++){
				*(chain+i+j*TOTAL_TIME)=XX[j];
			}
		}else{i--;}				//If fails, retry
	}
}
			

int main(int argc, const char* argv[]){
	srand(time(NULL));
	FILE* fp;
	if(!(fp=fopen(FILENAME,"w"))){fprintf(stderr,"Fopen error when opening output file!\n");exit(0);}

	double *MarkovChain;
	if(!(MarkovChain=malloc(sizeof(*MarkovChain)*SIZE_OF_VARIABLES*TOTAL_TIME)))
		{fprintf(stderr,"Malloc error when allocating MarkovChain!\n");exit(0);}
	
	initial_condition(MarkovChain);

	time_evolution(MarkovChain);

	for(int i=0;i<SIZE_OF_VARIABLES;i++){
		if(fwrite(MarkovChain+i*TOTAL_TIME,sizeof(*MarkovChain),TOTAL_TIME,fp)!=TOTAL_TIME)
			{fprintf(stderr,"Fwrite error when writing %dth variable!\n",i);exit(0);}
		
	}
	
	return 0;
}

