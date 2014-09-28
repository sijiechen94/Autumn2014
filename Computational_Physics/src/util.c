#include "util.h"
#include "math.h"

unsigned long partition(double* v, unsigned long low, unsigned long high);

int doubleSort(double* v, unsigned long low, unsigned long high){
	if(low<high){
		unsigned long pivotloc=partition(v,low,high);
		doubleSort(v,low,pivotloc-1);
		doubleSort(v,pivotloc+1,high);
	}
	return 0;
}

unsigned long partition(double* v, unsigned long low, unsigned long high){
	double pivotkey=v[low];
	unsigned long i=low;
	unsigned long j=high;
	v[0]=v[low];
	while(i<j){
		while(j>i&&v[j]>=pivotkey)
			j--;
		v[i]=v[j];
		while(i<j&&v[i]<=pivotkey)
			i++;
		v[j]=v[i];
	}
	v[i]=v[0];
	return i;
}
