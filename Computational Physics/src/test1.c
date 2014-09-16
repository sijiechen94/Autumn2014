#include "1.h"
#include "stdio.h"

int main(){
	int seed=2;
	FILE *output=fopen("./output/1.output","w");
	for(int i=0; i<50000; i++){
		fwrite(&seed,4,1,output);
		seed=schrage(seed);
		fwrite(&seed,4,1,output);
	}
	return 0;
}
