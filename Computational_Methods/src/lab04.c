#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIM 9
#define INPUTFILE "input4.txt"
#define OUTPUTFILE "output4.txt"
#define MAXTEMP 10000
#define EPSILON 1E-6

double norm(double* p1, double *p2){
	double max=0;
	for(int i=0; i<DIM; i++){
		double d=fabs(p1[i]-p2[i]);
		max=d>max?d:max;
	}
	return max;
}

int main(int argc, const char* argv[]){

	double A[DIM][DIM];
	double B[DIM][DIM];
	double Y[DIM];
	double g[DIM];
	double X1[DIM];
	double X2[DIM];

	FILE *input,*output;
	if(!(input=fopen(INPUTFILE,"r"))){fprintf(stderr,"Fopen error!\n");exit(0);}
	if(!(output=fopen(OUTPUTFILE,"w"))){fprintf(stderr,"Fopen error!\n");exit(0);}
	for(int i=0; i<DIM; i++){
		for(int j=0; j<DIM; j++){
			if(fscanf(input,"%lf",&(A[i][j]))!=1){fprintf(stderr,"Fscanf error! i=%d, j=%d\n ",i,j);exit(0);}
		}
		if(A[i][i]==0){fprintf(stderr,"Warning! A[%d][%d] is ZERO! Quitting...\n",i,i);exit(0);}
		if(fscanf(input,"%lf",&(Y[i]))!=1){fprintf(stderr,"Fscanf error! i=%d, j=%d\n ",i,DIM);exit(0);}
	}
	fclose(input);


	for(int k=1; k<=99; k++){
		for(int i=0; i<DIM; i++){
			g[i]=Y[i]/A[i][i];
			X1[i]=0;
			X2[i]=1;
			for(int j=0; j<DIM; j++){
				B[i][j]=i==j?0:-A[i][j]/A[i][i];
			}
		}
		/*for(int i=0;i<DIM;i++){
			printf("B[%d]\t",i);
			for(int j=0;j<DIM;j++){
				printf("%lf\t",B[i][j]);
			}
			printf("G[%d]:%lf\n",i,g[i]);
		}*/
		double w=k/50.0;
		int t=0;
		for(; t<MAXTEMP; t++){
			for(int i=0; i<DIM; i++)  X1[i]=X2[i];
			for(int i=0; i<DIM; i++){
				double s=g[i];
				for(int j=0; j<DIM; j++){		
					s+=B[i][j]*X2[j];
				}
				X2[i]=(1-w)*X1[i]+w*s;
			}
			if(norm(X1,X2)<EPSILON) break;
		}

		for(int i=0; i<DIM; i++){
			fprintf(output,"%19.16le\t",X2[i]);
		}
		fprintf(output,"Attemp:%d,w=%lf\n",t,w);
	}
	return 0;
}
	
