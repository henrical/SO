#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define FILES_NUM 5
#define STRING_SIZE 16

#define EOL '\n'

//gera um inteiro aleatorio entre min e max
int random_number(int min, int max)
{
	int result;

	max = max + 1; 
	
	srand(time(NULL));
	
	result = (rand()%(max-min)) + min;

	return result;
}


//le um ficheiro inteiro e coloca-o num array de chars
char *readFile(char *fileName)
{
	FILE *pFile;
	char *buffer;
	int c, pos = 0;	

	int size = 1024;

	buffer = (char*) malloc(size);

	pFile = fopen(fileName, "r"); 					

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
		assert(1);
	}


	fclose(pFile);

	return buffer;

}

int main()
{
	int i = 1;

	char fileNameArray[FILES_NUM][STRING_SIZE] =  {"SO2014-0.txt", "SO2014-1.txt", "SO2014-2.txt", "SO2014-3.txt", "SO2014-4.txt"};
	
	FILE *pFile;
	char *buffer;	
	char letter;


	//le todo o ficheiro e coloca o conteudo no buffer
	buffer = readFile(fileNameArray[random_number(0,4)]);

	
	//guarda a letra que e repetida
	letter = buffer[0];

	while(i<=1024) 
	{
				
		i++;
	}

	return 0;

}


