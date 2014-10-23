/*
 * ESCRITOR - ESCREVE UMA CADEIA ALEATORIA DE CARATERES NUM FICHEIRO ALEATORIO
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h> 

 int random_number(int max)  //gera numeros aleatorios entre 0 e max
{
  int result;
  srand(time(NULL));
  result = (rand() % max);
  return result;
}

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

void WriteToFile(){
  int times = 5120; 			//quantidade de ciclos a executar
  
  while(times-- != 0){
    int string_pos = random_number(10);		 //posicao do array string a utilizar
    int file_pos = random_number(5);			 //posicao do array files a utilizar
    int write_cycle = 1024; 			//quantidade de escritas a realizar
    
    
    int file = open(files[file_pos], O_RDWR|O_CREAT, S_IRWXU|S_IROTH);  //O_RDWR - modo de acesso Read Write ao ficheio
																		//O_CREAT - criar ficheiro se não existir
																		//S_IRWXU - permissao Read, Write, Execute para dono do ficheiro
																		//S_IROTH - permissao Read para outros utilizadores
    
    while(write_cycle-- != 0)				 //Ciclo de escrita demasiado rapido --> DELAY!
      write(file, strings[string_pos], 10); 
    
          
    close(file);
  }
  
}







