#include "math.h"
#include "stdio.h"
#include "stdlib.h"

static int k;
double h=1;

long power(int base, int power){
	long v=1;
	for(int i=0; i<power; i++){
		v*=base;
	}
	return v;
}

double summation(int start, int end, double x, double (*function)(int)){
	double sum=0;
	for(int i=start; i<=end; i++){
		sum+=function(i);
	}
	return sum;
}

double hk(int k){
	return h/power(2,k-1);
}

double fun(int i){
	return log(1+(2*i-1)*hk(k));
}

#define M 20

int main(){
	double* R_Table;
	R_Table=malloc(M*M*sizeof(double));
	double eps=0.0001;
	k=1;
	R_Table[1*M+1]=(log(1)+log(2))/2.0;
	for(k=2;k<=M;k++){
		R_Table[k*M+1]=(R_Table[(k-1)*M+1]+hk(k-1)*summation(1,power(2,k-2),1,fun))/2.0;
		for(int j=2; j<=k; j++){
			R_Table[k*M+j]=R_Table[k*M+j-1]+(R_Table[k*M+j-1]-R_Table[(k-1)*M+j-1])/(double)(power(4,j-1)-1);
		}
		if(fabs(R_Table[k*M+k]-R_Table[(k-1)*M+(k-1)])<eps) break;
	}
	printf("K=%d\n",k);
	for(int i=1; i<=k; i++){
		for(int j=1; j<=i; j++){
			printf("%.5lf ",R_Table[i*M+j]);
		}
		printf("\n");
	}
	return 0;
}
