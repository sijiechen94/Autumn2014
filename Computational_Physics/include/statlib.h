#include "stdlib.h"
#include "util.h"
#include "stdio.h"
#include "math.h"
#include "string.h"

#define BUFFERSIZE 0x4000

//   mean: Calculate the algebraic average of given vector
//USAGE
/****    v	vector                      ****/
/****    size   length of the vector        ****/
/****    result store the result            ****/
//RETURN VALUE
/****    0 if succeed                       ****/
/****    1 if input is wrong                ****/
int mean(double* v, unsigned long size, double* result);

//   momentum: Calculate the Kth central momentum of given vector
//USAGE
/****    v	vector                      ****/
/****    size   length of the vector        ****/
/****    k	kth momentum                ****/
/****    result store the result            ****/
//RETURN VALUE
/****    0 if succeed                       ****/
/****    1 if input is wrong                ****/
int momentum(double* v, unsigned long size, int k, double* result);
