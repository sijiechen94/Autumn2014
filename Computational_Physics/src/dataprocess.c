#include "stdlib.h"
#include "stdio.h"

int main(){
	unsigned long j=0;
	fwrite(&j,sizeof(unsigned long),1,stdout);
	double x;
	while(scanf("%lf",&x)>0){
		fwrite(&x,sizeof(double),1,stdout);
		scanf("%lf",&x);
		fwrite(&x,sizeof(double),1,stdout);
		j++;
	}
	fseek(stdout, 0L, SEEK_SET);
	fwrite(&j,sizeof(unsigned long),1,stdout);
	return 0;
}
