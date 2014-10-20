#include "discreteCDF.h"

#define SIZE 0x1000000
#define ALPHA 2.3

int main(){
	POINTS data;
	makecdf(&data,stdin);
        for(int i=0;i<SIZE;){
		long k=arc4random()%840000;
		double v=(k>=266000?(k-266000)/41000+2995:k/2800+2900);
                double u=foo4random();
                if(ALPHA*u<cmf(data,k)/(k>=266000?(41.0/840):(28.0/8400))){    //Success
        		fwrite(&v,sizeof(double),1,stdout);
			i++;
		}
        }   
        return 0;
}
    
