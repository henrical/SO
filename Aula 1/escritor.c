#include <stdio.h>
#include <stdlib.h>

#define CICLES_NUM 1024

#define STRINGS_NUM 10
#define FILES_NUM 5

#define STRING_SIZE 16


//gera um inteiro aleatorio entre min e max
int random_number(int min, int max)
{
	int result;

	max = max + 1; 
	
	srand(time(NULL));
	
	result = (rand()%(max-min)) + min;

	return result;
}



int main()
{
	int i = 0, e = 0;
	
	char charSequencesArray[STRINGS_NUM][STRING_SIZE] = {"aaaaaaaaa\n", "bbbbbbbbb\n", "ccccccccc\n", "ddddddddd\n", "eeeeeeeee\n", "fffffffff\n", "ggggggggg\n", "hhhhhhhhh\n", "iiiiiiiii\n", "jjjjjjjjj\n"};

	char fileNameArray[FILES_NUM][STRING_SIZE] =  {"SO2014-0.txt", "SO2014-1.txt", "SO2014-2.txt", "SO2014-3.txt", "SO2014-4.txt"};
	 
	FILE *pFile;

	//escolhe aleatoriamente o ficheiro onde vai escrever e a string que vais escrever
	int arrayNum; 
	int fileNum;
	
	while(e<5120)
	{
		arrayNum = random_number(0,9); //random char sequence - escolhe uma das posiçoes do array aleatoriamente
		fileNum = random_number(0,4); //random file name - escolhe uma das posiçoes do array aleatoriamente

		pFile = fopen( fileNameArray[fileNum], "w");
	
		if(pFile) //testa se realmente abriu/criou ficheiro
	  	  do{
			fprintf(pFile, charSequencesArray[arrayNum]);
			i++;	
	   	  }while(i < CICLES_NUM);	

		else 
	  	{
			printf("Error handling file\n");
			return EXIT_FAILURE;
	  	}

		i = 0;
		e++;
		fclose(pFile);
	} // while(e<5120)

	return EXIT_SUCCESS;
}
