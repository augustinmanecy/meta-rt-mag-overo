#include "ReadBinaryFile.h"
 
#define NB_DATA 4
 
int FdLog;

int main(int argc, char *argv[])
{
	char *FileName = argv[1];
	float ReadData[NB_DATA*NB_BYTE_FLOAT] = {0,};
	int NbBytesRead;
	int i;
	int cpt = 0;
	int NbLoop = 10;
	long int ReadTime;
	
	printf("%d\n", argc);
	
	if(argc == 3) 
	{
		NbLoop = strtol(argv[2], NULL, 10);
		printf("Try to read %d line of %s...\n", NbLoop, FileName);
	}
	else
	{
		printf("Syntax error: %s <FileName> <NbLineToRead>\n", argv[0]);
		return(0);
	}
	
	// open the file
	FdLog = open(argv[1], O_RDONLY);
	if (FdLog > 0)
	{
		printf("\t File successfully opened!!!\n");
	}
	else
	{
		perror("\t Can not open file: ");
		return(-1);
	}
	
	// read the real-time
	NbBytesRead = read(FdLog, &ReadTime, 8);
	if (NbBytesRead>0)
	{
		printf("%ld; ", ReadTime);
	}
	// Read the simultation time
	NbBytesRead = read(FdLog, &ReadTime, 8);
	if (NbBytesRead>0)
	{
		printf("%ld; ", ReadTime);
	}
	NbBytesRead = read(FdLog, ReadData, NB_DATA*NB_BYTE_FLOAT);
	cpt++;
	
	while(NbBytesRead>0 && cpt<NbLoop )
	{
		cpt++;
		 // read the real-time
	        NbBytesRead = read(FdLog, &ReadTime, 8);
        	if (NbBytesRead>0)
   	     	{
                	printf("%ld; ", ReadTime);
        	}
        	// Read the simultation time
        	NbBytesRead = read(FdLog, &ReadTime, 8);
        	if (NbBytesRead>0)
        	{
               		printf("%ld; ", ReadTime);
        	}

		NbBytesRead = read(FdLog, ReadData, NB_DATA*NB_BYTE_FLOAT);
		
		for(i=0; i<(NB_DATA-1); i++)
		{
			printf("%f; ", ReadData[i]);
		}
		printf("%f\n", ReadData[i]);
	}
	
	close(FdLog);
}

