#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h> 

#define ERROR_LOCK "Leitor - Erro a obter LOCK!\n"
#define ERROR_UNLOCK "LEITOR - Erro a libertar LOCK!\n"
#define MAX_STRING_POS 10
#define MAX_FILE_POS 5
#define LINES_NUM 1024
#define CHARS 10

const char *strings[10] ={
  "aaaaaaaaa\n", "bbbbbbbbb\n",
  "ccccccccc\n", "ddddddddd\n",
  "eeeeeeeee\n", "fffffffff\n",
  "ggggggggg\n", "hhhhhhhhh\n",
  "iiiiiiiii\n", "jjjjjjjjj\n"};

char *files[5] ={
  "SO2014-0.txt",  "SO2014-1.txt",
  "SO2014-2.txt",  "SO2014-3.txt",
  "SO2014-4.txt"};

  int random_number(int max)  //gera numeros aleatorios entre 0 e max
{
  int result;
  
  result = (rand() % max);
  return result;
}

  
int ReadFromFile(){
  srand(time(NULL));
  
  int times = LINES_NUM; 				//quantidade de escritas a realizar
  int file_pos = random_number(MAX_FILE_POS);		//posicao do array files a utilizar
  int i, bool = 1;						//bool > comparacao entre primeira linha e array strings
  
  char *buffer = (char*)malloc(CHARS*sizeof(char)), 
       *match = (char*)malloc(CHARS*sizeof(char));
  
  int file = open(files[file_pos], O_RDONLY, S_IRUSR|S_IROTH);	 //O_RDONLY - modo de acesso:leitura																                               //S_IROTH - permissao de Read para outros utilizadores
  
  int lock = flock(file, LOCK_SH);
  if(lock < 0)
    printf(ERROR_LOCK);
  
  int Ssize = read(file, buffer, 10);			 //le primeira linha e copia para buffer(10 caracteres)
  
  for(i = 0; i < MAX_STRING_POS; i++) //verifica se a linha lida é uma das linhas permitidas
  {			
    if(strcmp(strings[i], buffer) == 0)
    { 
		  bool = 0;
		  break;
    }
	}
  
  if(file > 0 && Ssize == CHARS && bool == 0){  
   strcpy(match, buffer);  
    
   while(times-- != 0)
   {
      Ssize = read(file, buffer, 10);  //copia a nova linha para o buffer
      if(strcmp(buffer, match) != 0 || Ssize != 10) //compara uma linha com a 1ª e se o numero de bytes lidos foi 10. Se alguma das condiçoes fallhar o ciclo termina
	      break;
   }
    
    lock = flock(file, LOCK_UN);
    if(lock < 0)
      printf(ERROR_UNLOCK);
    
    free(buffer);
    free(match);
    close(file);
    
    if(times != 0) 			 // se nao tiver lido 1024 linha ou ficheiro estiver errado termina com -1
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

int main(){
  
  printf("%d\n", ReadFromFile());
  
  return 0;
}