#ifndef VERDEX_DEFINES_h
 
	#define VERDEX_DEFINES_h
	
	#include "time_tools.h"				     /* Clock and delay customized tools */
	
	#ifndef ECHO_PRINTF
		#define ECHO_PRINTF	// printf disabled during simulation! (not during initialization...)
	#endif
	#ifndef ECHO_FPRINTF
			// fprintf (for debug only!) disabled during simulation! (not during initialization...)
	#endif	
	#ifndef ECHO_PRINTF_TIME
			// printf_time (for debug only!) disabled during simulation! (not during initialization...)
	#endif
	#ifndef ECHO_FPRINTF_TIME
			// fprintf_time (for debug only!) disabled during simulation! (not during initialization...)
	#endif
	#ifndef TASK_TIME_LOGGER
			// #define TASK_TIME_LOGGER
	#endif
	
	#define NB_BYTE_CHAR8 	1
	#define NB_BYTE_UCHAR8 	1
	#define NB_BYTE_INT16 	2
	#define NB_BYTE_UINT16 	2
	#define NB_BYTE_INT32 	4
	#define NB_BYTE_UINT32 	4
	#define NB_BYTE_FLOAT 	4
	#define NB_BYTE_DOUBLE 	8
	
	/***** DEFINE RS232 EXCHANGED DATA SIZE *****/
	
	/***** DEFINE UDP EXCHANGED DATA SIZE *****/
	
	/***** DEFINE SPI EXCHANGED DATA SIZE *****/
	
	/***** DEFINE I2C EXCHANGED DATA SIZE *****/
    	// number of I2C devices:  //(code generated automatically)
	#define NB_I2C_RECEPTION_DEV 2
	#define NB_I2C_EMISSION_DEV 2

	/***** DEFINE SAVE DATA SIZE (in the file "COM_InOut_Full_MultiTask_Clock_data_save.csv") *****/  //(code generated automatically)
	
	/***** DEFINE THE SAMPLE TIME *****/

	/***** TERMINATE DEFINES *****/
	
#endif
 
