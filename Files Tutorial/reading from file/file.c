#include <stdio.h>
#include <stdlib.h>

//this program reads and outputs the contents of a text file
int main(int argc, char *argv[])
{
	FILE *pFile;
	char *buffer;
	int c, pos = 0;	

	int size = 1024;

	buffer = (char*) malloc(size);

	pFile = fopen("example.txt", "r"); 					

	if(pFile)
		do{
			//reads a single character.
			c=fgetc(pFile);
		
			if(c != EOF) 
				buffer[pos++] = (char) c;

			//if buffer size nearly being exceded, increase memory alocated.
			if(pos >= size - 1)
			{
				size *= 1.5;
				buffer = (char*) realloc(buffer, size);
			}
			
		}while(c != EOF); //reads characters until end of file is found.	

	else
	{
		printf("Error handling file\n");
		return EXIT_FAILURE;
	}

	printf("%s", buffer);

	fclose(pFile);
	free(buffer);	

	return EXIT_SUCCESS;

}
