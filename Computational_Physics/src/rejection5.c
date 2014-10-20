/*  rejection5.c
 *
 *  Acceptance-rejection method for Assignment 5
 *  Use redirection to I/O
 */


#include "discreteARM.h"

#define SIZE 0x1000000

/*
 *  F(k) is defined as
 *    F(k) = 41000/840000 for 2995<=k<=3008
 *         =  2800/840000 for 2900<=k<=2994
 *  
 *  Inf(Alpha)=1/41000*840000/40123*373518)=2.2008
 *  To find a small alpha, you also need a more complex F(k),
 *  which makes locating v much more complex, rather than integer operations here
 */
#define ALPHA 2.201
#define F(k) ((k)>=266000?(41.0/840):(28.0/8400))

int main(){
	POINTS data;
	makepmf(&data,stdin);

	double* vector;
	vector=malloc(SIZE*sizeof(double));
	if(!vector) {printf("MALLOC ERROR!\n"); exit(0);}
        for(int i=0;i<SIZE;){
		long k=arc4random()%840000;
		double v=(k>=266000?(k-266000)/41000+2995:k/2800+2900);
                double u=foo4random();
                if(ALPHA*u<cmf(data,k)/F(k))    //Success
			vector[i++]=v;
        }   	
	fwrite(vector,sizeof(double),SIZE,stdout);
        return 0;
}
    
