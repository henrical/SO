#include <stdio.h>
#include <stdlib.h>

#define CICLES_NUM 5120

#define STRINGS_NUM 10
#define FILES_NUM 5

#define STRING_NAME_SIZE 10
#define FILE_NAME_SIZE 13


int main(int argc, char *argv[])
{
	int i;
	
	char charSequencesArray[STRINGS_NUM][STRING_NAME_SIZE] =
	 {"aaaaaaaaa\n", "bbbbbbbbb\n", "ccccccccc\n", "ddddddddd\n", "eeeeeeeee\n", "fffffffff\n", "ggggggggg\n", "hhhhhhhhh\n", "iiiiiiiii\n", "jjjjjjjjj\n"};

	char fileNameArray[FILES_NUM][FILE_NAME_SIZE] = 
	{"SO2014-0.txt", "SO2014-1.txt", "SO2014-2.txt", "SO2014-3.txt", "SO2014-4.txt"};
	 
	FILE *pFile;

	//escolhe o ficheiro onde vai escrever e a string que vais escrever
	int fileNum; //random file name
	int arrayNum; //random char sequence

	fileNum = 3;
	arrayNum = 2;

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

	fclose(pFile);

	return EXIT_SUCCESS;
}
