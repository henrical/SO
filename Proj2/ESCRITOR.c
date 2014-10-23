/*	ESCRITOR.c
 * 	FAZ BASICAMENTE O QUE O ANTERIOR FAZIA MAS AGORA 
 * 	RECEBE UM VALOR - 512 - COMO O NUMERO DE CICLOS
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h> 

#define ERROR "Erro na abertura do ficheiro!\n"
#define MAX_STRING_POS 10
#define MAX_FILE_POS 5
#define ITERATIONS 512
#define LINES_NUM 1024
#define BYTES_READ 10

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

 int random_number(int max)  		//MESMA FUNCAO - srand() SO E CHAMADO UMA VEZ
{					//MELHORA PRODUCAO DE ALEATORIOS IMENSO
  int result;
  result = (rand() % max);
  return result;
}

void WriteToFile(int times){
   srand(time(NULL));			//SELECAO DA SEMENTE DE NUMEROS ALEATORIOS
  
  while(times-- != 0){			//FUNCAO MANTEM-SE IDENTICA DAQUI PARA A FRENTE
    int string_pos = random_number(MAX_STRING_POS);
    int file_pos = random_number(MAX_FILE_POS);
    int lines_num = LINES_NUM;
    int file = open(files[file_pos], O_RDWR|O_CREAT, S_IRWXU|S_IROTH);  
    
    if(file != -1){
      while(lines_num-- != 0)
	write(file, strings[string_pos], BYTES_READ);
      
      close(file);
    }
    else
      printf(ERROR);
    
  }
  
}

int main(){
  
  WriteToFile(ITERATIONS);
  return 0;
}