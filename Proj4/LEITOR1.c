#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h> 

#define MAX_STRING_POS 10
#define MAX_FILE_POS 5
#define LINES_NUM 1024
#define CHARS 10
#define ERROR_LOCK "LEITOR1 - Erro a obter LOCK!\n"
#define ERROR_UNLOCK "LEITOR1 - Erro a libertar LOCK!\n"

// LEITOR APENAS TEVE DEFINICOES DE CONSTANTES E INCLUSAO DE LOCKS 
//NADA MAIS ALTERADO DO EXERCICIO 1

const char *strings[MAX_STRING_POS] ={
  "aaaaaaaaa\n", "bbbbbbbbb\n",
  "ccccccccc\n", "ddddddddd\n",
  "eeeeeeeee\n", "fffffffff\n",
  "ggggggggg\n", "hhhhhhhhh\n",
  "iiiiiiiii\n", "jjjjjjjjj\n"};

char *files[MAX_FILE_POS] ={
  "SO2014-0.txt",  "SO2014-1.txt",
  "SO2014-2.txt",  "SO2014-3.txt",
  "SO2014-4.txt"};

  
int ReadFromFile(int file_num){
  
  int times = LINES_NUM; 				
  int file_pos = file_num;	
  int i, bool = 1;						
  
  char *buffer = (char*)malloc(CHARS*sizeof(char)), 
       *match = (char*)malloc(CHARS*sizeof(char));
  
  int file = open(files[file_pos], O_RDONLY, S_IRUSR|S_IROTH);
  
  if( file > 0){
	  int lock = flock(file, LOCK_SH);
	  
	  if(lock < 0) 
		  printf(ERROR_LOCK);

	  int Ssize = read(file, buffer, CHARS);			 
	  
	  for(i = 0; i < MAX_STRING_POS; i++) 
	  {			
		if(strcmp(strings[i], buffer) == 0)
		{ 
			bool = 0;
			break;
		}
	  }
	 
	  if(Ssize == CHARS && bool == 0){                                     
												 
	   strcpy(match, buffer);  
		
	   while(times-- != 0)
	   {
		  Ssize = read(file, buffer, CHARS);  
		  if(strcmp(buffer, match) != 0 || Ssize != CHARS) 
			  break;
	   }
		
		lock = flock(file, LOCK_UN);
		if(lock < 0)
		  printf(ERROR_UNLOCK);
		
		free(buffer);
		free(match);
		close(file);
		
		if(times != 0) 			 
		  return -1;
		else
		  return 0;
	  } 
	  else
	  {
		lock = flock(file, LOCK_UN);
		if(lock < 0) 		
		  printf(ERROR_UNLOCK);
		
		free(buffer);
		free(match);
		
		close(file);
		return -1;
	  }
	}
	else
	  {
		free(buffer);
		free(match);
		return -1;
	  } 
  
}

int main(int argc, char *argv[]){
	int file_pos = atoi(argv[1]);
	
	//printf("%s \n", argv[1]);

	if(argc == 2 && file_pos >= 0 && file_pos < 5)
	{
		printf("%d\n", ReadFromFile(file_pos));		//argv[1] argumento passado pela bash/exec*
		return 0;
	}
	
	return -1;
}
