#include "discreteCDF.h"

#define RANDOM_SIZE 0x1000000

int main(int argc, const char* argv[]){
	POINTS data;
	makecdf(&data,stdin);
	printf("Length:%zu\n",data.length);
	for(int i=0; i<RANDOM_SIZE; i++){
		double u=data.x[searchIndex(data,foo4random())];
		fwrite(&u,sizeof(double),1,stdout);
	}
	return 0;
}
