/*  discreteARM.h
 *
 *  Header for Acceptance-Rejection Method for discrete RV
 *  Provides function interfaces and data structure
 *  Use redirection to I/O
 */

#include "stdlib.h"
#include "stdio.h"
#include <math.h>

/*
 *  Function-like macro used in searchIndex to improve readability
 */

#define isIndex(i) (data.y[(i)-1]<=v)&&(data.y[(i)]>v)
#define tooSmall(i) data.y[i-1]<=v

#define foo4random() ((double)rand()/RAND_MAX)      //convert uint32_t to double

typedef struct points{
	double *x;
	double *y;
	unsigned long length;
}POINTS;

int searchIndex(POINTS data, double v);

void makecmf(POINTS* data, FILE* datafile);

void makepmf(POINTS* data, FILE* datafile);

double cmf(POINTS data, long v);

double pmf(POINTS data, long v);

