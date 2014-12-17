/*	ESCRITOR-PAI FUNCOES fork() wait(status) execlp(path, file, args)
 * 	
 * 	ESSENCIA-> FAZ FORK(), GUARDA PID RESULTANTE, 
 * 	ESPERA FILHOS, FAZ OUTPUT TEMPO DE EXECUCAO
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <sys/time.h>

#define ERROR_FORK "ERRO! Processo-filho não foi criado.\n"
#define MAX 10
#define PATH "./ESCRITOR"
#define EXECUTABLE "ESCRITOR"

int main(){
  
  struct timeval tvstart, tvend, tvduration;
  unsigned long int duration;

  int times = 0, status = 0, valorExit, i;		//QTD DE CICLOS - TIPO DE RETORNO DE WAIT() 
  pid_t children[MAX];			//ARRAY COM PIDs DOS VARIOS P-FILHOS
  pid_t Pid;			//PID = PROCESS ID
  
  gettimeofday(&tvstart,NULL);
  
  while(times < MAX){
    children[times] = fork();		//FAZ FORK() E GUARDA O PID
    Pid = children[times];
    times++;
    
    if(Pid == 0){			//ESTAMOS NO FILHO
      execlp(PATH, EXECUTABLE, NULL);
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

