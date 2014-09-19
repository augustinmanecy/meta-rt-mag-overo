#include <sys/time.h>
#include "time_tools.h"
 
extern FILE *FID_debug;
 
// REMINDER

/*
struct timeval {
    time_t      tv_sec;     // seconds
    suseconds_t tv_usec;    // microseconds
};

struct timezone {
    int tz_minuteswest;     // minutes west of Greenwich
    int tz_dsttime;         // type of DST correction
};
*/
 
/*************** Declaration of different variable ***************/
extern struct TicToc struc_TicToc; // need to be created in main.c
 
/************ Declaration of functions and their body ************/
double ms_time (void) // give current time with millisecond resolution
{
	// average execution time is less than 4us (3.3us)
	static struct timeval tod;
	gettimeofday (&tod, NULL);
	return ((double)tod.tv_sec * 1000.0 + (double)tod.tv_usec / 1000.0);
}
 
double us_time (void) // give current time with microsecond resolution
{
	// average execution time is less than 3us (2.3us)
	static struct timeval tod;
	gettimeofday (&tod, NULL);
	return ((double)tod.tv_sec * 1000000.0 + (double)tod.tv_usec);
}

double s_time (void) // give current time with microsecond resolution
{
	// average execution time is less than 4us (3.2us)
	static struct timeval tod;
	gettimeofday (&tod, NULL);
	return ((double)tod.tv_sec + ((double)tod.tv_usec)/1000000.0);
}
 
void tic (char *message_in) // capture an initial time with microseconds resolution
{
	struc_TicToc.d_Tinit = us_time();
	strcpy(struc_TicToc.s_message, message_in);
	#ifdef ECHO_PRINTF_TIME
		printf("BEGIN Tic(): %s\n", struc_TicToc.s_message);
	#endif
	#ifdef ECHO_FPRINTF_TIME
		fprintf(FID_debug, "BEGIN Tic(): %s\n", struc_TicToc.s_message);
	#endif
	// printf("temps initial: %f us\n", struc_TicToc.d_Tinit);
}
 
double toc (void) // capture a final time with microseconds resolution
{
	struc_TicToc.d_Tend = us_time();
	struc_TicToc.d_Tdelta = struc_TicToc.d_Tend - struc_TicToc.d_Tinit;
	#ifdef ECHO_PRINTF_TIME
		printf("END Toc(): %s. Elapsed time: %.9f [ms]\n", struc_TicToc.s_message, (struc_TicToc.d_Tdelta)/1000.0);
	#endif
	#ifdef ECHO_FPRINTF_TIME
		fprintf(FID_debug, "END Toc(): %s. Elapsed time: %.9f [ms]\n", struc_TicToc.s_message, (struc_TicToc.d_Tdelta)/1000.0);
	#endif
	
	return(struc_TicToc.d_Tdelta);
}

void us_wait(int us_wait_time)
{
	double us_init_time = us_time();
	
	while((us_time()-us_init_time)<(double)us_wait_time);
}

void ms_wait(int ms_wait_time)
{
	double us_init_time = us_time();
	
	while((us_time()-us_init_time)<(double)ms_wait_time*1000.0);
}

void s_wait(int s_wait_time)
{
	double us_init_time = us_time();
	
	while((us_time()-us_init_time)<(double)s_wait_time*1000000.0);
}

