#include "stdlib.h"  //For Arc4 random generator
#include "stdio.h"   //For standard stream IO
#include "math.h"    //For definition of Pi, and library function acos()

#define ARC4RANDOM_MAX 0x100000000				//arc4random() returns 0~2**32-1
#define foo4random() ((double)arc4random()/ARC4RANDOM_MAX)	//convert uint32_t to double

#define N 3072	//Some random number to make figure clean and convincing

int main(){
	FILE *fp=fopen("./output/2.output","w");
	if(!fp) {printf("Open file error!\n"); exit(-1)}

	for(int i=0;i<N;i++){

		/*++++++++++++++++++++++++*/
		/*  R=1                   */
		/*  Phi=2*Pi*u            */
		/*  Theta=acos(1-2*u)     */
		/*  u is uniform on (0,1) */
		/*++++++++++++++++++++++++*/

		double coordinates[3]={1,2*M_PI*foo4random(),acos(1-2*foo4random())};
		fwrite(coordinates,sizeof(double),3,fp);
	}

	return 0;
}//main

	
