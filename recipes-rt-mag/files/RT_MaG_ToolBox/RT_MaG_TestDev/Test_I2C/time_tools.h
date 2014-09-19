#ifndef DEF_TIME_TOOLS
#define DEF_TIME_TOOLS

/*
Need a global variable "struc_TicToc" of type "TicToc" declared in main.c to work well! 
*/

#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include "defines_verdex.h"

/********** Declaration of data structure and new types **********/
struct TicToc {
	double d_Tinit;
	double d_Tend;
	double d_Tdelta;
	char s_message[100];
};

/************** Declaration of function's protoypes **************/
double ms_time (void);	// give current time in millisecond
double us_time (void);	// give current time in microsecond
double s_time (void); 	// give current time in second
void tic (char *message_in);
double toc (void);
void us_wait(int us_wait_time);
void ms_wait(int ms_wait_time);
void s_wait(int s_wait_time);

#endif
