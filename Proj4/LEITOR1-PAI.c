
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <sys/time.h>

#define ERROR_FORK "ERRO! Processo-filho não foi criado.\n"
#define MAX 3
#define MAX_FILE_POS 5
#define PATH "./LEITOR1"
#define EXECUTABLE "LEITOR1"

int random_number(int max)  
{
  int result;
  result = (rand() % max);
  return result;
}

int main(){  
  struct timeval tvstart, tvend, tvduration;
  unsigned long int duration;
  gettimeofday(&tvstart,NULL);
  srand((tvstart.tv_sec * 1000) + (tvstart.tv_usec / 1000));

  int times = 0, status = 0, valorExit, i;		//QTD DE CICLOS - TIPO DE RETORNO DE WAIT() 
  pid_t children[MAX];			//ARRAY COM PIDs DOS VARIOS P-FILHOS
  pid_t Pid;			//PID = PROCESS ID - Wret = 'valor retornado por Wait()'
  char *str = (char*)malloc(sizeof(char));
  
    
  gettimeofday(&tvstart,NULL);
  
  while(times < MAX){
    children[times] = fork();		//FAZ FORK() E GUARDA O PID
    Pid = children[times];
    times++;
    
    sprintf(str, "%d", random_number(MAX_FILE_POS));
    
    if(Pid == 0){			//ESTAMOS NO FILHO
      execlp(PATH, EXECUTABLE, str, NULL);
    }
    else if(Pid > 0) {			//ESTAMOS NO PAI
      continue;
    }
    else if(Pid == -1 ) {		//ERRO NA CRIACAO DO PROCESSO FILHO
      printf(ERROR_FORK);
    }
  }
  
  for(i=0; i < times; i++){
    Pid = children[i];
    
    if (wait (&status) == -1) {printf("Processo %d terminou com erro", Pid);}
    if (WIFEXITED(status)) {
      valorExit = (char) WEXITSTATUS(status);
      printf("Processo %d terminou e devolveu %d\n", Pid, valorExit);
    }
    else {printf("Processo %d terminou sem exit ou return", Pid);}
  }

  gettimeofday(&tvend,NULL);

  tvduration.tv_sec = tvend.tv_sec - tvstart.tv_sec;
  tvduration.tv_usec = tvend.tv_usec - tvstart.tv_usec;
  duration = tvduration.tv_sec * 1000000 + tvduration.tv_usec;
  
  printf("Tempo de execução : %ld microsegundos\n", duration);
  
  return 0;
}
