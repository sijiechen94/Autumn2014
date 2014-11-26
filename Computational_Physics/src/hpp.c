#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* bit representation */
#define FROM_LEFT	0x01
#define FROM_RIGHT	0x02
#define FROM_UP 	0x04
#define FROM_DOWN	0x08
#define TO_LEFT		0x10
#define TO_RIGHT	0x20
#define TO_UP		0x40
#define TO_DOWN		0x80
/* bit representation */

/* colors */
#define WHITE	0xFF
#define PALE	0xBF
#define GREY	0X7F
#define	DARK	0X3F
#define	BLACK	0X00
/* colors */

/* parameters */
#define MAPSIZE 192
#define OUTPUT_INTERVAL 5
#define MAXTIME 12000
#define NOISE_PROB 0.25
#define RADIUS_IN 20
#define RADIUS_OUT 30
#define CENTER_X -20
#define CENTER_Y 35
/* parameters */

/* Tags for gather */
#define INSIDE		0
#define UP_EDGE 	1
#define DOWN_EDGE	2
#define LEFT_EDGE	3
#define RIGHT_EDGE	4
/* Tags for gather */

typedef unsigned char point_t;

#define O2Cx(x) abs((x)-MAPSIZE/2-(CENTER_X)) //Coordinates transformation
#define O2Cy(x) abs((x)-MAPSIZE/2-(CENTER_Y)) //Coordinates transformation
#define range(x,y) sqrt(pow(O2Cx((x)),2)+pow(O2Cy((y)),2))

int init_pattern(point_t *map){
	int x,y;
	double r;

	for(int i=0; i<MAPSIZE*MAPSIZE; i++){
		x=i/MAPSIZE;
		y=i%MAPSIZE;
		r=range(x,y);
		if(r>=RADIUS_IN&&r<=RADIUS_OUT) *(map+i)=FROM_LEFT|FROM_RIGHT|FROM_UP|FROM_DOWN;
	}
	return 0;
}

int init_noise(point_t *map, double noise_rate){
	double u;
	if(noise_rate>=1){fprintf(stderr,"Noise is too big!\n");exit(0);}
	for(int i=0; i<MAPSIZE; i++){
		for(int j=0; j<MAPSIZE; j++){
			int ii=i*MAPSIZE+j;
			point_t temp=0;
			if(i==0||i==MAPSIZE-1||j==0||j==MAPSIZE-1) continue;
			if((i==1&&j==1)||(i==1&&j==MAPSIZE-2)||(i==MAPSIZE-2&&j==1)||(i==MAPSIZE-2&&j==MAPSIZE-2)) continue;

			//Apply noise on different directions independently			
			u=(double)rand()/RAND_MAX;
			if	(u<noise_rate)		temp=(temp|FROM_LEFT);
			u=(double)rand()/RAND_MAX;
			if	(u<noise_rate)		temp=(temp|FROM_RIGHT);
			u=(double)rand()/RAND_MAX;
			if	(u<noise_rate)		temp=(temp|FROM_UP);
			u=(double)rand()/RAND_MAX;
			if	(u<noise_rate)		temp=(temp|FROM_DOWN);
			//Apply noise on different directions independently			

			*(map+ii)=((*(map+ii))|temp);
		}
	}
	return 0;
}

int collision(point_t *map){
	point_t temp;
	for(int i=0; i<MAPSIZE*MAPSIZE; i++){
		temp=(*(map+i))%16;
		
		//Change directions while heads-on collision happens
		if(temp==(FROM_LEFT|FROM_RIGHT)) temp=(FROM_UP|FROM_DOWN);
		else if(temp==(FROM_UP|FROM_DOWN)) temp=(FROM_LEFT|FROM_RIGHT);
		//Change directions while heads-on collision happens

		*(map+i)=(*(map+i))%16+temp*16;
	}
	return 0;
}

int gather(point_t *out, point_t left, point_t right, point_t up, point_t down, int tag){
	point_t temp;
	
	if(tag==INSIDE){
		temp=(left&TO_RIGHT)|(right&TO_LEFT)|(up&TO_DOWN)|(down&TO_UP);
		temp/=16;
	}else if(tag==UP_EDGE)	{
		temp=(down&TO_UP)?FROM_DOWN:0;
	}else if(tag==DOWN_EDGE){
		temp=(up&TO_DOWN)?FROM_UP:0;
	}else if(tag==LEFT_EDGE){
		temp=(right&TO_LEFT)?FROM_RIGHT:0;
	}else if(tag==RIGHT_EDGE){
		temp=(left&TO_RIGHT)?FROM_LEFT:0;
	}else{
		fprintf(stderr,"Wrong Tag:%d (gather)\n",tag);
		exit(0);
	}
	*out=*out/16*16+temp;

	return 0;
}

int transport(point_t *map){
	for(int i=0; i<MAPSIZE; i++){
		for(int j=0; j<MAPSIZE; j++){
			int ii=i*MAPSIZE+j;
			
			//Determine tag
			int tag;
			if(i==0||i==MAPSIZE-1||j==0||j==MAPSIZE-1) continue;
			if((i==1&&j==1)||(i==1&&j==MAPSIZE-2)||(i==MAPSIZE-2&&j==1)||(i==MAPSIZE-2&&j==MAPSIZE-2)) continue;
			
			if	(i==1)		tag=UP_EDGE;
			else if	(i==MAPSIZE-2)	tag=DOWN_EDGE;
			else if	(j==1)		tag=LEFT_EDGE;
			else if	(j==MAPSIZE-2)	tag=RIGHT_EDGE;
			else 			tag=INSIDE;
			//End determine tag

			gather(map+ii,*(map+ii-1),*(map+ii+1),*(map+ii-MAPSIZE),*(map+ii+MAPSIZE),tag);
		}
	}
	return 0;
}

int output(point_t *map){
	FILE *fp;
	if(!(fp=fopen("hpp.dat","a"))){fprintf(stderr,"Fopen error!\n");exit(0);};
	point_t temp;
	unsigned char color;
	int n;
	for(int i=0; i<MAPSIZE; i++){
		for(int j=0; j<MAPSIZE; j++){
		
			//Determine number of particles at the point
			n=0;
			temp=*(map+i*MAPSIZE+j);
			if((temp&FROM_UP)==FROM_UP) n++;
			if((temp&FROM_DOWN)==FROM_DOWN) n++;
			if((temp&FROM_LEFT)==FROM_LEFT) n++;
			if((temp&FROM_RIGHT)==FROM_RIGHT) n++;
			//Determine number of particles at the point

			//Determin grey scale
			if(n==0) color=WHITE;
			else if(n==1) color=PALE;
			else if(n==2) color=GREY;
			else if(n==3) color=DARK;
			else color=BLACK;
			//Determin grey scale
			
			fputc(color,fp);
			fflush(fp);
		}
	}
	fclose(fp);
	return 0;
}

int main(int argc, const char* argv[]){

	point_t *map;
	if(!(map=malloc(sizeof(point_t)*MAPSIZE*MAPSIZE))){fprintf(stderr,"Malloc error!\n");exit(0);}
	memset(map,0,MAPSIZE*MAPSIZE);//Clean heap
	
	if(init_pattern(map)!=0){fprintf(stderr,"init_pattern failed!\n");exit(0);}
	if(init_noise(map,NOISE_PROB)!=0){fprintf(stderr,"init_noise failed!\n");exit(0);}
	if(output(map)!=0){fprintf(stderr,"init_noise failed!\n");exit(0);}
	for(int i=0; i<MAXTIME; i++){
		if(collision(map)!=0){fprintf(stderr,"init_noise failed!\n");exit(0);}
		if(transport(map)!=0){fprintf(stderr,"init_noise failed!\n");exit(0);}
		if(!(i%OUTPUT_INTERVAL)){
			if(output(map)!=0){fprintf(stderr,"init_noise failed!\n");exit(0);}
		}
	}

	return 0;
}
