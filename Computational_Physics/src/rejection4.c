/*  rejection4.c
 *
 *  Acceptance-rejection method for Assignment 4
 *  Use redirection to I/O
 */

#include <math.h>
#include "stdio.h"
#include "stdlib.h"

#define foo4random() ((double)rand()/RAND_MAX)


/*  Inf(Alpha)=1.520285391
 *  Alpha is taken to be PI/2 so that Alpha*Cauchy(x) does not have PI
 */
#define SIZE 0x1000000
#define M_1_SQRT2PI 0.39894228040143267793994605993438186847
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif
#define Gauss(x) (M_1_SQRT2PI*exp(-(x)*(x)*0.5))
#define AlphaCauchy(x) (0.5/(1+(x)*(x)))

int main(){
    int i=0;
    double *vector;
    vector=malloc(SIZE*sizeof(double));
    if(!vector) {printf("MALLOC ERROR!\n"); exit(0);}
    while(1){
        double u=tan(M_PI*(foo4random()-0.5));;
        double v=foo4random();
        if(v<Gauss(u)/(AlphaCauchy(u))){    //Success
            vector[i++]=u;
            if(i==SIZE) break;
        }
    }
    fwrite(vector,sizeof(double),SIZE,stdout);
    return 0;
}