/*  discreteARM.c
 *
 *  Implementation for Acceptance-Rejection Method for discrete RV
 */

#include "discreteARM.h"

/*  These two function are specifically written for Assignment 5,
 *  and is therefore not portable.
 */
double pmf(POINTS data, long k){
	int i=(k>=266000?(k-266000)/41000+95:k/2800);
        return k<2800?data.y[0]:data.y[i]-data.y[i-1];
}

double cmf(POINTS data, long k){
	int i=(k>=266000?(k-266000)/41000+95:k/2800);
	return data.y[i];
}	

int searchIndex(POINTS data, double v){ 
        unsigned long mid, j=data.length, i=0;
        while(1){
                mid=(j+i)/2;
                if (isIndex(mid)) break;
                else if (tooSmall(mid)) i=mid;
                else j=mid;
        }   
        return mid;
}    

void makecmf(POINTS* data, FILE* datafile){
        fread(&(data->length),sizeof(unsigned long),1,datafile);
        data->x=malloc(data->length*sizeof(double));
        data->y=malloc(data->length*sizeof(double));
	if(!data->x&&!data->y) {printf("MALLOC ERROR!\n"); exit(0);}
        for(int i=0; i<data->length; i++){
                fread(&(data->x[i]),sizeof(double),1,datafile);
                fread(&(data->y[i]),sizeof(double),1,datafile);
                if(i) data->y[i]+=data->y[i-1];
        }   
        for(int i=0; i<data->length; i++)
                data->y[i]=data->y[i]/data->y[data->length-1];  //Normalization
}

void makepmf(POINTS* data, FILE* datafile){
	long sum=0;
        fread(&(data->length),sizeof(unsigned long),1,datafile);
        data->x=malloc(data->length*sizeof(double));
        data->y=malloc(data->length*sizeof(double));
	if(!data->x&&!data->y) {printf("MALLOC ERROR!\n"); exit(0);}
        for(int i=0; i<data->length; i++){
                fread(&(data->x[i]),sizeof(double),1,datafile);
                fread(&(data->y[i]),sizeof(double),1,datafile);
		sum+=data->y[i];
        }   
        for(int i=0; i<data->length; i++)
                data->y[i]=data->y[i]/sum;;  //Normalization
}
