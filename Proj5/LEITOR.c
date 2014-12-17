#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define THREAD_ERROR "LEITOR - ERRO NA CRIACAO DA THREAD"
#define T_JOIN_ERROR "LEITOR - Erro a fazer join de thread!\n"
#define ERROR_FILE_NAME "LEITOR - Nome de Ficheiro em formato errado!\n"
#define ERROR_SEM_I "LEITOR - Erro a inicializar semaforo\n"
#define ERROR_SEM_D "LEITOR - Erro a destruir semaforo\n"
#define ERROR_MUTEX_I "LEITOR - Erro a inicializar mutex\n"
#define ERROR_MUTEX_D "LEITOR - Erro a destruir mutex\n"
#define ERROR_CLOSE "LEITOR - Erro a fechar o ficheiro!\n"
#define ERROR_LOCK "LEITOR - Erro a obter LOCK!\n"
#define ERROR_UNLOCK "LEITOR - Erro a libertar LOCK!\n"
#define ERROR_WAIT "LEITOR - Erro a esperar no semáforo\n"
#define ERROR_MUTEX_L "LEITOR - Erro a bloquear o mutex\n"
#define ERROR_MUTEX_UN "LEITOR - Erro a desbloquear o mutex\n"
#define ERROR_POST "LEITOR - Erro a assinalar o semáforo\n"

#define THREAD_NUM 10
#define NUM_FILES 5
#define MAX_STRING_POS 10
#define STRING_SIZE 10
#define LINES_NUM 1024
#define MAX_FILE_POS 5
#define BYTES_TO_READ 13

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
  
int insert_pos = 0, remove_pos = 0, runnable = 1;

sem_t full, empty;
pthread_mutex_t mutex; 

char *sh_buffer[NUM_FILES];

int isFileNameCorrect(char *fname)
{
  int i;
	
	if(fname[0] == '\n' || fname[0] == ' ' || fname[0] == '\0' )
		return 0;
	
  for(i = 0; i < MAX_FILE_POS; i++)
  {
    if(strcmp(fname, files[i]) == 0)
    {
      return 1;
    }
  }
  return 0;
}

void addToSharedBuffer(char *fname)
{
  if(isFileNameCorrect(fname))
  {
    //critical section begins
    if(sem_wait(&empty) != 0)
			printf(ERROR_WAIT);
    if(pthread_mutex_lock(&mutex) != 0)
			printf(ERROR_MUTEX_L);
    
    strcpy(sh_buffer[insert_pos], fname);

    if(insert_pos == NUM_FILES-1)
      insert_pos = 0;
    else insert_pos++;
    
    if(pthread_mutex_unlock(&mutex) != 0)
			printf(ERROR_MUTEX_UN);
		
    if(sem_post(&full) != 0)
			printf(ERROR_POST);
    //critical section ends
  }
  else
		printf(ERROR_FILE_NAME);
}




