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
#include <sys/time.h>

#define ERROR "Erro na abertura do ficheiro!\n"
#define ERROR_LOCK "Escritor - Erro a obter LOCK!\n"
#define ERROR_UNLOCK "Escritor - Erro a libertar LOCK!\n"
#define MAX_STRING_POS 10
#define MAX_FILE_POS 5
#define ITERATIONS 512
#define LINES_NUM 1024
#define BYTES_READ 10

struct timeval tvstart, tvend, tvduration;
long int flock_min = 999999999;
long int flock_max = 0;
unsigned int duration;

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
  gettimeofday(&tvstart,NULL);
  srand((tvstart.tv_sec * 1000) + (tvstart.tv_usec / 1000));//SELECAO DA SEMENTE DE NUMEROS ALEATORIOS

  while(times-- != 0){			//FUNCAO MANTEM-SE IDENTICA DAQUI PARA A FRENTE
    int string_pos = random_number(MAX_STRING_POS);
    int file_pos = random_number(MAX_FILE_POS);
    int lines_num = LINES_NUM;
    
    gettimeofday(&tvstart, NULL);
    
    int file = open(files[file_pos], O_RDWR|O_CREAT, S_IRWXU|S_IROTH);
    int lock = flock(file, LOCK_EX);
    
     if(lock < 0)
       printf(ERROR_LOCK);
    gettimeofday(&tvend, NULL);
    
    if(file != -1){
      while(lines_num-- != 0)
	write(file, strings[string_pos], BYTES_READ);
    }
    else
      printf(ERROR);
    
    lock = flock(file, LOCK_UN);
    if(lock < 0) 
      printf(ERROR_UNLOCK);
   
    
    close(file);
    
    tvduration.tv_sec = tvend.tv_sec - tvstart.tv_sec;
	tvduration.tv_usec = tvend.tv_usec - tvstart.tv_usec;
	duration = tvduration.tv_sec * 1000000 + tvduration.tv_usec;
		
	if (duration >= flock_max)
		flock_max = duration;
	else
		flock_min = duration;

  }
  
    printf("Tempo mínimo de espera do flock: %ld microsegundos\n", flock_min);
    printf("Tempo máximo de espera do flock: %ld microsegundos\n", flock_max);
  
}

int main(){
  
  WriteToFile(ITERATIONS);
  return 0;
}
