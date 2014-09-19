#include "library_I2C.h"

// extern pointer to debug_file (defined in main)
extern FILE *FID_debug;
 
// name of I2C devices
static const char *I2C_DeviceList[NB_MAX_I2C_DEV] = {"/dev/i2c-1", "/dev/i2c-2", "/dev/i2c-3"};
// file descriptor for I2C I2C_DeviceList
static int I2C_dev[NB_MAX_I2C_DEV];

int32_t InitI2Cbus(uint32_t deviceNum)
{
	int32_t ret = 0;
	
	printf("I2C initialisation...\n");
	fprintf(FID_debug, "I2C initialisation...\n");
	printf("Try to open %s...\n", I2C_DeviceList[deviceNum]);
	// open the file descriptor
	I2C_dev[deviceNum] = open(I2C_DeviceList[deviceNum], O_RDWR );
	printf("plop\n");
	fflush(stdout);
	if (I2C_dev[deviceNum] < 0)
	{
		perror("can't open I2C device");
		fprintf(FID_debug, "can't open I2C device\n");
		return(-1);
	}
	
	printf("I2C device '%s' successfully opened!!!\n", I2C_DeviceList[deviceNum]);
	fprintf(FID_debug, "I2C device '%s' successfully opened!!!\n", I2C_DeviceList[deviceNum]);
	
	return(0);
}

void CloseI2Cbus(uint32_t deviceNum)
{
	if (close(I2C_dev[deviceNum]) == 0)
	{
		printf("I2C device '%s' successfully closed!!!\n", I2C_DeviceList[deviceNum]);
		fprintf(FID_debug, "I2C device '%s' successfully closed!!!\n", I2C_DeviceList[deviceNum]);
	}
	else
	{
		printf("Can not close I2C device '%s'!!!\n", I2C_DeviceList[deviceNum]);
		fprintf(FID_debug, "Can not close I2C device '%s'!!!\n", I2C_DeviceList[deviceNum]);
	}
}

/*********************************** DOUBLE ***********************************/

int32_t SendnDouble_I2C(uint32_t deviceNum, double *ToSend, uint32_t NbToSend, uint8_t slaveAddress)
{
	
	int32_t n_sent;
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToSend = NbToSend*NB_BYTE_DOUBLE;
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// send the data
	n_sent = write(I2C_dev[deviceNum], ToSend, NbBytesToSend);
	
	#ifdef ECHO_PRINTF
		printf("<I2C> SendnDouble_I2C...\n");
		if (n_sent >= 1)
		{
			printf("\t %d bytes sent\n\t", n_sent);
			for(i=0; i<NbToSend; i++)
			{
				printf("%f ", ToSend[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not send I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> SendnDouble_I2C...\n");
		if (n_sent >= 1)
		{
			fprintf(FID_debug, "\t %d bytes sent\n\t", n_sent);
			for(i=0; i<NbToSend; i++)
			{
				fprintf(FID_debug, "%f ", ToSend[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(n_sent);
}

int32_t ReadnDouble_I2C(uint32_t deviceNum, double *ToRead, uint32_t NbToRead, uint8_t slaveAddress)
{
	// Read n Char8 and send arbitrary (0) n char8 (because I2C work in full duplex)
	int32_t n_read;
	int32_t index = 0;
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToRead = NbToRead*NB_BYTE_DOUBLE;
	
	#ifdef ECHO_PRINTF
		printf("<I2C> ReadnDouble_I2C...\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> ReadnDouble_I2C...\n");
	#endif
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// read the data
	n_read = read(I2C_dev[deviceNum], ToRead, NbBytesToRead);
	while(n_read>0)
	{
		index+=n_read;
		#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
			#ifdef ECHO_PRINTF
				printf("%d ", index);
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "%d ", index);
			#endif
		#endif
		n_read = read(I2C_dev[deviceNum], ToRead+index, NbBytesToRead-index);
	}
	
	#ifdef ECHO_PRINTF
		if (index >= 1)
		{
			printf("\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				printf("%f ", ToRead[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not read I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		if (index >= 1)
		{
			fprintf(FID_debug, "\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				fprintf(FID_debug, "%f ", ToRead[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(index);
}

int32_t WaitnDouble_I2C(uint32_t deviceNum, double *ToRead, uint32_t NbToRead, uint8_t slaveAddress, int32_t BlockingTimeOut_us)
{
	// Read n Char8 and send arbitrary (0) n char8 (because I2C work in full duplex)
	int32_t n_read;
	int32_t index = 0;
	int32_t dt;
	struct timeval InitTime, CurrentTime;
	
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToRead = NbToRead*NB_BYTE_DOUBLE;
	
	gettimeofday(&InitTime, NULL);;	// recover current time in micro_seconds
	
	#ifdef ECHO_PRINTF
		printf("<I2C> WaitnDouble_I2C...\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> WaitnDouble_I2C...\n");
	#endif
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// read the data
	n_read = read(I2C_dev[deviceNum], ToRead, NbBytesToRead);
	while(n_read>=0)
	{
		if(n_read == 0)
		{
			gettimeofday(&CurrentTime, NULL);;	// recover current time in micro_seconds
			dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
				+ CurrentTime.tv_usec - InitTime.tv_usec;
			if (dt > BlockingTimeOut_us)
			{
				#ifdef ECHO_PRINTF
					printf("<I2C> Wait TIME OUT!\n");
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "<I2C> Wait TIME OUT!\n");
				#endif
				return(-1);
			}
		}
		else
		{
			index+=n_read;
			#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
				#ifdef ECHO_PRINTF
					printf("%d ", index);
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "%d ", index);
				#endif
			#endif
			n_read = read(I2C_dev[deviceNum], ToRead+index, NbBytesToRead-index);
		}
	}
	
	#ifdef ECHO_PRINTF
		if (index >= 1)
		{
			printf("\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				printf("%f ", ToRead[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not read I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		if (index >= 1)
		{
			fprintf(FID_debug, "\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				fprintf(FID_debug, "%f ", ToRead[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(index);
}


/*********************************** FLOAT ***********************************/
int32_t SendnFloat_I2C(uint32_t deviceNum, float *ToSend, uint32_t NbToSend, uint8_t slaveAddress)
{
	
	int32_t n_sent;
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToSend = NbToSend*NB_BYTE_FLOAT;
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// send the data
	n_sent = write(I2C_dev[deviceNum], ToSend, NbBytesToSend);
	
	#ifdef ECHO_PRINTF
		printf("<I2C> SendnFloat_I2C...\n");
		if (n_sent >= 1)
		{
			printf("\t %d bytes sent\n\t", n_sent);
			for(i=0; i<NbToSend; i++)
			{
				printf("%f ", ToSend[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not send I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> SendnFloat_I2C...\n");
		if (n_sent >= 1)
		{
			fprintf(FID_debug, "\t %d bytes sent\n\t", n_sent);
			for(i=0; i<NbToSend; i++)
			{
				fprintf(FID_debug, "%f ", ToSend[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(n_sent);
}

int32_t ReadnFloat_I2C(uint32_t deviceNum, float *ToRead, uint32_t NbToRead, uint8_t slaveAddress)
{
	// Read n Char8 and send arbitrary (0) n char8 (because I2C work in full duplex)
	int32_t n_read;
	int32_t index = 0;
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToRead = NbToRead*NB_BYTE_FLOAT;
	
	#ifdef ECHO_PRINTF
		printf("<I2C> ReadnFloat_I2C...\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> ReadnFloat_I2C...\n");
	#endif
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// read the data
	n_read = read(I2C_dev[deviceNum], ToRead, NbBytesToRead);
	while(n_read>0)
	{
		index+=n_read;
		#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
			#ifdef ECHO_PRINTF
				printf("%d ", index);
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "%d ", index);
			#endif
		#endif
		n_read = read(I2C_dev[deviceNum], ToRead+index, NbBytesToRead-index);
	}
	
	#ifdef ECHO_PRINTF
		if (index >= 1)
		{
			printf("\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				printf("%f ", ToRead[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not read I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		if (index >= 1)
		{
			fprintf(FID_debug, "\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				fprintf(FID_debug, "%f ", ToRead[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(index);
}

int32_t WaitnFloat_I2C(uint32_t deviceNum, float *ToRead, uint32_t NbToRead, uint8_t slaveAddress, int32_t BlockingTimeOut_us)
{
	// Read n Char8 and send arbitrary (0) n char8 (because I2C work in full duplex)
	int32_t n_read;
	int32_t index = 0;
	int32_t dt;
	struct timeval InitTime, CurrentTime;
	
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToRead = NbToRead*NB_BYTE_FLOAT;
	
	gettimeofday(&InitTime, NULL);;	// recover current time in micro_seconds
	
	#ifdef ECHO_PRINTF
		printf("<I2C> WaitnFloat_I2C...\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> WaitnFloat_I2C...\n");
	#endif
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// read the data
	n_read = read(I2C_dev[deviceNum], ToRead, NbBytesToRead);
	while(n_read>=0)
	{
		if(n_read == 0)
		{
			gettimeofday(&CurrentTime, NULL);;	// recover current time in micro_seconds
			dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
				+ CurrentTime.tv_usec - InitTime.tv_usec;
			if (dt > BlockingTimeOut_us)
			{
				#ifdef ECHO_PRINTF
					printf("<I2C> Wait TIME OUT!\n");
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "<I2C> Wait TIME OUT!\n");
				#endif
				return(-1);
			}
		}
		else
		{
			index+=n_read;
			#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
				#ifdef ECHO_PRINTF
					printf("%d ", index);
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "%d ", index);
				#endif
			#endif
			n_read = read(I2C_dev[deviceNum], ToRead+index, NbBytesToRead-index);
		}
	}
	
	#ifdef ECHO_PRINTF
		if (index >= 1)
		{
			printf("\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				printf("%f ", ToRead[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not read I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		if (index >= 1)
		{
			fprintf(FID_debug, "\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				fprintf(FID_debug, "%f ", ToRead[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(index);
}

/*********************************** INT32 ***********************************/

int32_t SendnInt32_I2C(uint32_t deviceNum, int32_t *ToSend, uint32_t NbToSend, uint8_t slaveAddress)
{
	
	int32_t n_sent;
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToSend = NbToSend*NB_BYTE_INT32;
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// send the data
	n_sent = write(I2C_dev[deviceNum], ToSend, NbBytesToSend);
	
	#ifdef ECHO_PRINTF
		printf("<I2C> SendnInt32_I2C...\n");
		if (n_sent >= 1)
		{
			printf("\t %d bytes sent\n\t", n_sent);
			for(i=0; i<NbToSend; i++)
			{
				printf("%d ", ToSend[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not send I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> SendnInt32_I2C...\n");
		if (n_sent >= 1)
		{
			fprintf(FID_debug, "\t %d bytes sent\n\t", n_sent);
			for(i=0; i<NbToSend; i++)
			{
				fprintf(FID_debug, "%d ", ToSend[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(n_sent);
}

int32_t ReadnInt32_I2C(uint32_t deviceNum, int32_t *ToRead, uint32_t NbToRead, uint8_t slaveAddress)
{
	// Read n Char8 and send arbitrary (0) n char8 (because I2C work in full duplex)
	int32_t n_read;
	int32_t index = 0;
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToRead = NbToRead*NB_BYTE_INT32;
	
	#ifdef ECHO_PRINTF
		printf("<I2C> ReadnInt32_I2C...\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> ReadnInt32_I2C...\n");
	#endif
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// read the data
	n_read = read(I2C_dev[deviceNum], ToRead, NbBytesToRead);
	while(n_read>0)
	{
		index+=n_read;
		#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
			#ifdef ECHO_PRINTF
				printf("%d ", index);
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "%d ", index);
			#endif
		#endif
		n_read = read(I2C_dev[deviceNum], ToRead+index, NbBytesToRead-index);
	}
	
	#ifdef ECHO_PRINTF
		if (index >= 1)
		{
			printf("\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				printf("%d ", ToRead[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not read I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		if (index >= 1)
		{
			fprintf(FID_debug, "\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				fprintf(FID_debug, "%d ", ToRead[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(index);
}

int32_t WaitnInt32_I2C(uint32_t deviceNum, int32_t *ToRead, uint32_t NbToRead, uint8_t slaveAddress, int32_t BlockingTimeOut_us)
{
	// Read n Char8 and send arbitrary (0) n char8 (because I2C work in full duplex)
	int32_t n_read;
	int32_t index = 0;
	int32_t dt;
	struct timeval InitTime, CurrentTime;
	
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToRead = NbToRead*NB_BYTE_INT32;
	
	gettimeofday(&InitTime, NULL);;	// recover current time in micro_seconds
	
	#ifdef ECHO_PRINTF
		printf("<I2C> WaitnInt32_I2C...\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> WaitnInt32_I2C...\n");
	#endif
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// read the data
	n_read = read(I2C_dev[deviceNum], ToRead, NbBytesToRead);
	while(n_read>=0)
	{
		if(n_read == 0)
		{
			gettimeofday(&CurrentTime, NULL);;	// recover current time in micro_seconds
			dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
				+ CurrentTime.tv_usec - InitTime.tv_usec;
			if (dt > BlockingTimeOut_us)
			{
				#ifdef ECHO_PRINTF
					printf("<I2C> Wait TIME OUT!\n");
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "<I2C> Wait TIME OUT!\n");
				#endif
				return(-1);
			}
		}
		else
		{
			index+=n_read;
			#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
				#ifdef ECHO_PRINTF
					printf("%d ", index);
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "%d ", index);
				#endif
			#endif
			n_read = read(I2C_dev[deviceNum], ToRead+index, NbBytesToRead-index);
		}
	}
	
	#ifdef ECHO_PRINTF
		if (index >= 1)
		{
			printf("\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				printf("%d ", ToRead[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not read I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		if (index >= 1)
		{
			fprintf(FID_debug, "\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				fprintf(FID_debug, "%d ", ToRead[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(index);
}

/*********************************** UINT32 ***********************************/
int32_t SendnUInt32_I2C(uint32_t deviceNum, uint32_t *ToSend, uint32_t NbToSend, uint8_t slaveAddress)
{
	
	int32_t n_sent;
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToSend = NbToSend*NB_BYTE_UINT32;
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// send the data
	n_sent = write(I2C_dev[deviceNum], ToSend, NbBytesToSend);
	
	#ifdef ECHO_PRINTF
		printf("<I2C> SendnUInt32_I2C...\n");
		if (n_sent >= 1)
		{
			printf("\t %d bytes sent\n\t", n_sent);
			for(i=0; i<NbToSend; i++)
			{
				printf("%u ", ToSend[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not send I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> SendnUInt32_I2C...\n");
		if (n_sent >= 1)
		{
			fprintf(FID_debug, "\t %d bytes sent\n\t", n_sent);
			for(i=0; i<NbToSend; i++)
			{
				fprintf(FID_debug, "%u ", ToSend[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(n_sent);
}

int32_t ReadnUInt32_I2C(uint32_t deviceNum, uint32_t *ToRead, uint32_t NbToRead, uint8_t slaveAddress)
{
	// Read n Char8 and send arbitrary (0) n char8 (because I2C work in full duplex)
	int32_t n_read;
	int32_t index = 0;
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToRead = NbToRead*NB_BYTE_UINT32;
	
	#ifdef ECHO_PRINTF
		printf("<I2C> ReadnUInt32_I2C...\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> ReadnUInt32_I2C...\n");
	#endif
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// read the data
	n_read = read(I2C_dev[deviceNum], ToRead, NbBytesToRead);
	while(n_read>0)
	{
		index+=n_read;
		#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
			#ifdef ECHO_PRINTF
				printf("%d ", index);
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "%d ", index);
			#endif
		#endif
		n_read = read(I2C_dev[deviceNum], ToRead+index, NbBytesToRead-index);
	}
	
	#ifdef ECHO_PRINTF
		if (index >= 1)
		{
			printf("\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				printf("%u ", ToRead[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not read I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		if (index >= 1)
		{
			fprintf(FID_debug, "\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				fprintf(FID_debug, "%u ", ToRead[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(index);
}

int32_t WaitnUInt32_I2C(uint32_t deviceNum, uint32_t *ToRead, uint32_t NbToRead, uint8_t slaveAddress, int32_t BlockingTimeOut_us)
{
	// Read n Char8 and send arbitrary (0) n char8 (because I2C work in full duplex)
	int32_t n_read;
	int32_t index = 0;
	int32_t dt;
	struct timeval InitTime, CurrentTime;
	
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToRead = NbToRead*NB_BYTE_UINT32;
	
	gettimeofday(&InitTime, NULL);;	// recover current time in micro_seconds
	
	#ifdef ECHO_PRINTF
		printf("<I2C> WaitnUInt32_I2C...\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> WaitnUInt32_I2C...\n");
	#endif
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// read the data
	n_read = read(I2C_dev[deviceNum], ToRead, NbBytesToRead);
	while(n_read>=0)
	{
		if(n_read == 0)
		{
			gettimeofday(&CurrentTime, NULL);;	// recover current time in micro_seconds
			dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
				+ CurrentTime.tv_usec - InitTime.tv_usec;
			if (dt > BlockingTimeOut_us)
			{
				#ifdef ECHO_PRINTF
					printf("<I2C> Wait TIME OUT!\n");
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "<I2C> Wait TIME OUT!\n");
				#endif
				return(-1);
			}
		}
		else
		{
			index+=n_read;
			#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
				#ifdef ECHO_PRINTF
					printf("%d ", index);
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "%d ", index);
				#endif
			#endif
			n_read = read(I2C_dev[deviceNum], ToRead+index, NbBytesToRead-index);
		}
	}
	
	#ifdef ECHO_PRINTF
		if (index >= 1)
		{
			printf("\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				printf("%u ", ToRead[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not read I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		if (index >= 1)
		{
			fprintf(FID_debug, "\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				fprintf(FID_debug, "%u ", ToRead[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(index);
}
/*********************************** INT16 ***********************************/

int32_t SendnInt16_I2C(uint32_t deviceNum, int16_t *ToSend, uint32_t NbToSend, uint8_t slaveAddress)
{
	
	int32_t n_sent;
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToSend = NbToSend*NB_BYTE_INT16;
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// send the data
	n_sent = write(I2C_dev[deviceNum], ToSend, NbBytesToSend);
	
	#ifdef ECHO_PRINTF
		printf("<I2C> SendnInt16_I2C...\n");
		if (n_sent >= 1)
		{
			printf("\t %d bytes sent\n\t", n_sent);
			for(i=0; i<NbToSend; i++)
			{
				printf("%d ", ToSend[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not send I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> SendnInt16_I2C...\n");
		if (n_sent >= 1)
		{
			fprintf(FID_debug, "\t %d bytes sent\n\t", n_sent);
			for(i=0; i<NbToSend; i++)
			{
				fprintf(FID_debug, "%d ", ToSend[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(n_sent);
}

int32_t ReadnInt16_I2C(uint32_t deviceNum, int16_t *ToRead, uint32_t NbToRead, uint8_t slaveAddress)
{
	// Read n Char8 and send arbitrary (0) n char8 (because I2C work in full duplex)
	int32_t n_read;
	int32_t index = 0;
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToRead = NbToRead*NB_BYTE_INT16;
	
	#ifdef ECHO_PRINTF
		printf("<I2C> ReadnInt16_I2C...\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> ReadnInt16_I2C...\n");
	#endif
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// read the data
	n_read = read(I2C_dev[deviceNum], ToRead, NbBytesToRead);
	while(n_read>0)
	{
		index+=n_read;
		#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
			#ifdef ECHO_PRINTF
				printf("%d ", index);
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "%d ", index);
			#endif
		#endif
		n_read = read(I2C_dev[deviceNum], ToRead+index, NbBytesToRead-index);
	}
	
	#ifdef ECHO_PRINTF
		if (index >= 1)
		{
			printf("\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				printf("%d ", ToRead[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not read I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		if (index >= 1)
		{
			fprintf(FID_debug, "\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				fprintf(FID_debug, "%d ", ToRead[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(index);
}

int32_t WaitnInt16_I2C(uint32_t deviceNum, int16_t *ToRead, uint32_t NbToRead, uint8_t slaveAddress, int32_t BlockingTimeOut_us)
{
	// Read n Char8 and send arbitrary (0) n char8 (because I2C work in full duplex)
	int32_t n_read;
	int32_t index = 0;
	int32_t dt;
	struct timeval InitTime, CurrentTime;
	
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToRead = NbToRead*NB_BYTE_INT16;
	
	gettimeofday(&InitTime, NULL);;	// recover current time in micro_seconds
	
	#ifdef ECHO_PRINTF
		printf("<I2C> WaitnInt16_I2C...\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> WaitnInt16_I2C...\n");
	#endif
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// read the data
	n_read = read(I2C_dev[deviceNum], ToRead, NbBytesToRead);
	while(n_read>=0)
	{
		if(n_read == 0)
		{
			gettimeofday(&CurrentTime, NULL);;	// recover current time in micro_seconds
			dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
				+ CurrentTime.tv_usec - InitTime.tv_usec;
			if (dt > BlockingTimeOut_us)
			{
				#ifdef ECHO_PRINTF
					printf("<I2C> Wait TIME OUT!\n");
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "<I2C> Wait TIME OUT!\n");
				#endif
				return(-1);
			}
		}
		else
		{
			index+=n_read;
			#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
				#ifdef ECHO_PRINTF
					printf("%d ", index);
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "%d ", index);
				#endif
			#endif
			n_read = read(I2C_dev[deviceNum], ToRead+index, NbBytesToRead-index);
		}
	}
	
	#ifdef ECHO_PRINTF
		if (index >= 1)
		{
			printf("\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				printf("%d ", ToRead[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not read I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		if (index >= 1)
		{
			fprintf(FID_debug, "\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				fprintf(FID_debug, "%d ", ToRead[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(index);
}

/*********************************** UINT16 ***********************************/
int32_t SendnUInt16_I2C(uint32_t deviceNum, uint16_t *ToSend, uint32_t NbToSend, uint8_t slaveAddress)
{
	
	int32_t n_sent;
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToSend = NbToSend*NB_BYTE_UINT16;
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// send the data
	n_sent = write(I2C_dev[deviceNum], ToSend, NbBytesToSend);
	
	#ifdef ECHO_PRINTF
		printf("<I2C> SendnUInt16_I2C...\n");
		if (n_sent >= 1)
		{
			printf("\t %d bytes sent\n\t", n_sent);
			for(i=0; i<NbToSend; i++)
			{
				printf("%u ", ToSend[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not send I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> SendnUInt16_I2C...\n");
		if (n_sent >= 1)
		{
			fprintf(FID_debug, "\t %d bytes sent\n\t", n_sent);
			for(i=0; i<NbToSend; i++)
			{
				fprintf(FID_debug, "%u ", ToSend[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(n_sent);
}

int32_t ReadnUInt16_I2C(uint32_t deviceNum, uint16_t *ToRead, uint32_t NbToRead, uint8_t slaveAddress)
{
	// Read n Char8 and send arbitrary (0) n char8 (because I2C work in full duplex)
	int32_t n_read;
	int32_t index = 0;
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToRead = NbToRead*NB_BYTE_UINT16;
	
	#ifdef ECHO_PRINTF
		printf("<I2C> ReadnUInt16_I2C...\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> ReadnUInt16_I2C...\n");
	#endif
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// read the data
	n_read = read(I2C_dev[deviceNum], ToRead, NbBytesToRead);
	while(n_read>0)
	{
		index+=n_read;
		#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
			#ifdef ECHO_PRINTF
				printf("%d ", index);
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "%d ", index);
			#endif
		#endif
		n_read = read(I2C_dev[deviceNum], ToRead+index, NbBytesToRead-index);
	}
	
	#ifdef ECHO_PRINTF
		if (index >= 1)
		{
			printf("\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				printf("%u ", ToRead[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not read I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		if (index >= 1)
		{
			fprintf(FID_debug, "\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				fprintf(FID_debug, "%u ", ToRead[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(index);
}

int32_t WaitnUInt16_I2C(uint32_t deviceNum, uint16_t *ToRead, uint32_t NbToRead, uint8_t slaveAddress, int32_t BlockingTimeOut_us)
{
	// Read n Char8 and send arbitrary (0) n char8 (because I2C work in full duplex)
	int32_t n_read;
	int32_t index = 0;
	int32_t dt;
	struct timeval InitTime, CurrentTime;
	
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToRead = NbToRead*NB_BYTE_UINT16;
	
	gettimeofday(&InitTime, NULL);;	// recover current time in micro_seconds
	
	#ifdef ECHO_PRINTF
		printf("<I2C> WaitnUInt16_I2C...\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> WaitnUInt16_I2C...\n");
	#endif
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// read the data
	n_read = read(I2C_dev[deviceNum], ToRead, NbBytesToRead);
	while(n_read>=0)
	{
		if(n_read == 0)
		{
			gettimeofday(&CurrentTime, NULL);;	// recover current time in micro_seconds
			dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
				+ CurrentTime.tv_usec - InitTime.tv_usec;
			if (dt > BlockingTimeOut_us)
			{
				#ifdef ECHO_PRINTF
					printf("<I2C> Wait TIME OUT!\n");
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "<I2C> Wait TIME OUT!\n");
				#endif
				return(-1);
			}
		}
		else
		{
			index+=n_read;
			#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
				#ifdef ECHO_PRINTF
					printf("%d ", index);
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "%d ", index);
				#endif
			#endif
			n_read = read(I2C_dev[deviceNum], ToRead+index, NbBytesToRead-index);
		}
	}
	
	#ifdef ECHO_PRINTF
		if (index >= 1)
		{
			printf("\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				printf("%u ", ToRead[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not read I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		if (index >= 1)
		{
			fprintf(FID_debug, "\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				fprintf(FID_debug, "%u ", ToRead[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(index);
}
/*********************************** CHAR8 ***********************************/

int32_t SendnInt8_I2C(uint32_t deviceNum, int8_t *ToSend, uint32_t NbToSend, uint8_t slaveAddress)
{
	
	int32_t n_sent;
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToSend = NbToSend*NB_BYTE_CHAR8;
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// send the data
	n_sent = write(I2C_dev[deviceNum], ToSend, NbBytesToSend);
	
	#ifdef ECHO_PRINTF
		printf("<I2C> SendnInt8_I2C...\n");
		if (n_sent >= 1)
		{
			printf("\t %d bytes sent\n\t", n_sent);
			for(i=0; i<NbToSend; i++)
			{
				printf("%d ", ToSend[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not send I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> SendnInt8_I2C...\n");
		if (n_sent >= 1)
		{
			fprintf(FID_debug, "\t %d bytes sent\n\t", n_sent);
			for(i=0; i<NbToSend; i++)
			{
				fprintf(FID_debug, "%d ", ToSend[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(n_sent);
}

int32_t ReadnInt8_I2C(uint32_t deviceNum, int8_t *ToRead, uint32_t NbToRead, uint8_t slaveAddress)
{
	// Read n Char8 and send arbitrary (0) n char8 (because I2C work in full duplex)
	int32_t n_read;
	int32_t index = 0;
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToRead = NbToRead*NB_BYTE_CHAR8;
	
	#ifdef ECHO_PRINTF
		printf("<I2C> ReadnInt8_I2C...\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> ReadnInt8_I2C...\n");
	#endif
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// read the data
	n_read = read(I2C_dev[deviceNum], ToRead, NbBytesToRead);
	while(n_read>0)
	{
		index+=n_read;
		#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
			#ifdef ECHO_PRINTF
				printf("%d ", index);
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "%d ", index);
			#endif
		#endif
		n_read = read(I2C_dev[deviceNum], ToRead+index, NbBytesToRead-index);
	}
	
	#ifdef ECHO_PRINTF
		if (index >= 1)
		{
			printf("\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				printf("%d ", ToRead[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not read I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		if (index >= 1)
		{
			fprintf(FID_debug, "\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				fprintf(FID_debug, "%d ", ToRead[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(index);
}

int32_t WaitnInt8_I2C(uint32_t deviceNum, int8_t *ToRead, uint32_t NbToRead, uint8_t slaveAddress, int32_t BlockingTimeOut_us)
{
	// Read n Char8 and send arbitrary (0) n char8 (because I2C work in full duplex)
	int32_t n_read;
	int32_t index = 0;
	int32_t dt;
	struct timeval InitTime, CurrentTime;
	
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToRead = NbToRead*NB_BYTE_CHAR8;
	
	gettimeofday(&InitTime, NULL);;	// recover current time in micro_seconds
	
	#ifdef ECHO_PRINTF
		printf("<I2C> WaitnInt8_I2C...\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> WaitnInt8_I2C...\n");
	#endif
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// read the data
	n_read = read(I2C_dev[deviceNum], ToRead, NbBytesToRead);
	while(n_read>=0)
	{
		if(n_read == 0)
		{
			gettimeofday(&CurrentTime, NULL);;	// recover current time in micro_seconds
			dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
				+ CurrentTime.tv_usec - InitTime.tv_usec;
			if (dt > BlockingTimeOut_us)
			{
				#ifdef ECHO_PRINTF
					printf("<I2C> Wait TIME OUT!\n");
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "<I2C> Wait TIME OUT!\n");
				#endif
				return(-1);
			}
		}
		else
		{
			index+=n_read;
			#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
				#ifdef ECHO_PRINTF
					printf("%d ", index);
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "%d ", index);
				#endif
			#endif
			n_read = read(I2C_dev[deviceNum], ToRead+index, NbBytesToRead-index);
		}
	}
	
	#ifdef ECHO_PRINTF
		if (index >= 1)
		{
			printf("\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				printf("%d ", ToRead[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not read I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		if (index >= 1)
		{
			fprintf(FID_debug, "\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				fprintf(FID_debug, "%d ", ToRead[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(index);
}

/*********************************** UCHAR8 ***********************************/
int32_t SendnUInt8_I2C(uint32_t deviceNum, uint8_t *ToSend, uint32_t NbToSend, uint8_t slaveAddress)
{
	
	int32_t n_sent;
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToSend = NbToSend*NB_BYTE_UCHAR8;
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// send the data
	n_sent = write(I2C_dev[deviceNum], ToSend, NbBytesToSend);
	
	#ifdef ECHO_PRINTF
		printf("<I2C> SendnUInt8_I2C...\n");
		if (n_sent >= 1)
		{
			printf("\t %d bytes sent\n\t", n_sent);
			for(i=0; i<NbToSend; i++)
			{
				printf("%u ", ToSend[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not send I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> SendnUInt8_I2C...\n");
		if (n_sent >= 1)
		{
			fprintf(FID_debug, "\t %d bytes sent\n\t", n_sent);
			for(i=0; i<NbToSend; i++)
			{
				fprintf(FID_debug, "%u ", ToSend[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(n_sent);
}

int32_t ReadnUInt8_I2C(uint32_t deviceNum, uint8_t *ToRead, uint32_t NbToRead, uint8_t slaveAddress)
{
	// Read n Char8 and send arbitrary (0) n char8 (because I2C work in full duplex)
	int32_t n_read;
	int32_t index = 0;
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToRead = NbToRead*NB_BYTE_UCHAR8;
	
	#ifdef ECHO_PRINTF
		printf("<I2C> ReadnUInt8_I2C...\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> ReadnUInt8_I2C...\n");
	#endif
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// read the data
	n_read = read(I2C_dev[deviceNum], ToRead, NbBytesToRead);
	while(n_read>0)
	{
		index+=n_read;
		#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
			#ifdef ECHO_PRINTF
				printf("%d ", index);
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "%d ", index);
			#endif
		#endif
		n_read = read(I2C_dev[deviceNum], ToRead+index, NbBytesToRead-index);
	}
	
	#ifdef ECHO_PRINTF
		if (index >= 1)
		{
			printf("\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				printf("%u ", ToRead[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not read I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		if (index >= 1)
		{
			fprintf(FID_debug, "\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				fprintf(FID_debug, "%u ", ToRead[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(index);
}

int32_t WaitnUInt8_I2C(uint32_t deviceNum, uint8_t *ToRead, uint32_t NbToRead, uint8_t slaveAddress, int32_t BlockingTimeOut_us)
{
	// Read n Char8 and send arbitrary (0) n char8 (because I2C work in full duplex)
	int32_t n_read;
	int32_t index = 0;
	int32_t dt;
	struct timeval InitTime, CurrentTime;
	
	#if (defined(ECHO_PRINTF)||(defined(ECHO_FPRINTF)))
		uint32_t i;
	#endif
	uint32_t NbBytesToRead = NbToRead*NB_BYTE_UCHAR8;
	
	gettimeofday(&InitTime, NULL);;	// recover current time in micro_seconds
	
	#ifdef ECHO_PRINTF
		printf("<I2C> WaitnUInt8_I2C...\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<I2C> WaitnUInt8_I2C...\n");
	#endif
	
	// choose the slave
	ioctl(I2C_dev[deviceNum], I2C_SLAVE, slaveAddress);
	// read the data
	n_read = read(I2C_dev[deviceNum], ToRead, NbBytesToRead);
	while(n_read>=0)
	{
		if(n_read == 0)
		{
			gettimeofday(&CurrentTime, NULL);;	// recover current time in micro_seconds
			dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
				+ CurrentTime.tv_usec - InitTime.tv_usec;
			if (dt > BlockingTimeOut_us)
			{
				#ifdef ECHO_PRINTF
					printf("<I2C> Wait TIME OUT!\n");
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "<I2C> Wait TIME OUT!\n");
				#endif
				return(-1);
			}
		}
		else
		{
			index+=n_read;
			#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
				#ifdef ECHO_PRINTF
					printf("%d ", index);
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "%d ", index);
				#endif
			#endif
			n_read = read(I2C_dev[deviceNum], ToRead+index, NbBytesToRead-index);
		}
	}
	
	#ifdef ECHO_PRINTF
		if (index >= 1)
		{
			printf("\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				printf("%u ", ToRead[i]);
			}
			printf("\n");
		}
		else
		{
			perror("Can not read I2C message!");
		}
	#endif
	#ifdef ECHO_FPRINTF
		if (index >= 1)
		{
			fprintf(FID_debug, "\t %d bytes read\n\t", index);
			for(i=0; i<NbToRead; i++)
			{
				fprintf(FID_debug, "%u ", ToRead[i]);
			}
			fprintf(FID_debug, "\n");
		}
		else
		{
			fprintf(FID_debug, "Can not send I2C message!");
		}
	#endif
	
	return(index);
}

