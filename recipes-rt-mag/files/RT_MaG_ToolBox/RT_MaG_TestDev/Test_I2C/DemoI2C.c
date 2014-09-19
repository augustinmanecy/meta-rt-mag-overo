/*
  Simple I2C communication test with an Arduino as the slave device 
  using the library_I2C of RT-MaG toolbox.
  The program sends an array of counter to the Arduino, which responds with 
  the same array of counter incremented by 1. Then the pregram sends the new 
  counter value until reach 256. 
*/

#include "library_I2C.h"

#define ARDUINO_I2C_ADDRESS 0x10
#define ARDUINO_I2C_BUFFER_LIMIT 32
#define ARRAY_SIZE 10
#define NB_LOOP 255
#define BLOCKING_TIME_us 100

	// relative to time_tools
struct TicToc struc_TicToc;    	// to use tic() and toc() functions of time_tools.h
//real_T rT_MyClock_s;			// to simulate a clock in secondes
//real_T rT_TimeInit_s;			// to memorize initial time in second
	// debug file and pipe to send command to the system
FILE * FID_debug;				// to debug
 
int main(int argc, char **argv)
{
	int DeviceNum;	// 0 for "/dev/i2c-1", 
					// 1 for "/dev/i2c-2", 
					// 2 for "/dev/i2c-3"
	unsigned char ToSend[ARRAY_SIZE];
	unsigned char Received[ARRAY_SIZE];
	int i;
	int j;
	char TransmissionError=0;
	
	if (argc!=2)
	{
		printf("SYNTAX: %s <i2c device num>\n",argv[0]);
		printf("         e.g., '%s 1' (for device '/dev/i2c-1')\n\n",argv[0]);
		
		return(0);
	}	
	else
	{
		if (!strcmp(argv[1],"-help")||!strcmp(argv[1],"-h"))
		{
			printf("SYNTAX: %s <i2c device num>\n",argv[0]);
			printf("         e.g., '%s 1' (for device '/dev/i2c-1')\n\n",argv[0]);
			return(0);
		}
		else
		{
			DeviceNum = (int)strtol(argv[1],NULL, 10)-1;
			printf("Device: %d\n", DeviceNum);
		}
	}
	
	// open the debug file
	FID_debug = fopen("Test_I2C.debug", "w");
	
	// initialize the device
	InitI2Cbus(DeviceNum);

	// initialize the counter
	for(i=0; i<ARRAY_SIZE; i++)
	{
		ToSend[i] = i;
	}
	for(i=0;i<NB_LOOP; i++)
	{
		// send the first counter
		SendnUInt8_I2C(DeviceNum, ToSend, ARRAY_SIZE, ARDUINO_I2C_ADDRESS);
		
		// receive the value
		WaitnUInt8_I2C(DeviceNum, Received, ARRAY_SIZE, ARDUINO_I2C_ADDRESS, BLOCKING_TIME_us);
		
		// check the data
		for (j=0;j<ARRAY_SIZE;j++)
		{
			if(ToSend[j]+1 != Received[j])
			{
				printf("Transmission error: ToSend[%d]=%u and Received[%d]=%u\n", j, ToSend[j], j, Received[j]);
				TransmissionError = 1;
			}
			ToSend[j]++;
		}
	}
	
	// Give results of test
	if(!TransmissionError)
	{
		printf("test Transmission successfully done!\n");
	}
	else
	{
		printf("test Transmission failed!\n");
	}
	
	// close the device
	CloseI2Cbus(DeviceNum);

	// close the debug file
	fclose(FID_debug);
	
	return(0);
}