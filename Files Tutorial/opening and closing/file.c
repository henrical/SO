#define MSG "This is the information age."

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *pFile;

	pFile = fopen("/home/saasbook/SO/Files Tutorial/test.txt", "w"); 
	printf("file opened!\n");					
				// modes:  "r" - read, file has to exist
				//         "w" - write, cannot read, creates new file if inexistant, deletes if already exists
				//         "a" - append (adds to end of file), creates new if inexistant, deletes old and creates new if it exists
				//         "r+" - read and write, file has to exist
				// 	   "w+" - creates a new file if there is none, deletes file and creates new if it already exists
				//         "a+" - does not delete old file if it exists
				// adding a "b" at the end of all modes creates a binary file.	

	if(pFile!=NULL)
	{
		fprintf(pFile, MSG);
		fclose(pFile);
		printf("file closed!\n");
		
	}	

	else
		printf("Error handling file\n");
	

	return EXIT_SUCCESS;

}
