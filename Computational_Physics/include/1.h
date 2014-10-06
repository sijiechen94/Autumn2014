#include "stdint.h"

//Max number for seed
#define SCHRAGE_MAX 0x80000000UL

/***    Interfaces      ***/

/***    schrage         ***/
//Getting next random number
double schrage();

/***    sschrage        ***/
//Setting seed for PRNG
//Usage: seed can be either positive or negative
void sschrage(int32_t seed);
