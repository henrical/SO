#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define FILES_NUM 5
#define STRING_SIZE 16

#define TRUE 0
#define FALSE -1

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
		assert(1); //the program stops
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

	char *fileName; 
	fileName = fileNameArray[random_number(0,4)];


	//le todo o ficheiro e coloca o conteudo no buffer
	buffer = readFile(fileName);

	
	//printf("ficheiro escolhido: %s\n", fileName);

	
	//guarda a letra que e repetida
	letter = buffer[0];

	while(i<=10240) 
	{
		if(i%10==0)
		{
			if(buffer[i-1]!= EOL) 
			{
				/*printf("%d\n", i);				
				printf("failure, barra-n error\n");*/
				
				return FALSE; 
				
			}
		}

		else
		{
			if(buffer[i-1]!= letter)
			{
				 /*printf("%d\n", i);
				 printf("failure, letter error\n");*/

				 return FALSE;
				 
			}
		}
					
		i++;
	}

	printf("sucesso\nlidos %d caracteres\n", i-1); 

	return TRUE;

}


