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
  
  struct timeval t_start, t_end, t_duration;

  int times = 0, status = 0;		//QTD DE CICLOS - TIPO DE RETORNO DE WAIT() 
  pid_t children[MAX];			//ARRAY COM PIDs DOS VARIOS P-FILHOS
  pid_t Pid, Wret;			//PID = PROCESS ID - Wret = 'valor retornado por Wait()'
  
  gettimeofday(&t_start,NULL);
  
  while(times < MAX){
    children[times] = fork();		//FAZ FORK() E GUARDA O PID
    Pid = children[times];
    times++;
    
    if(Pid == 0){			//ESTAMOS NO FILHO
      execlp(PATH, EXECUTABLE, NULL);
      exit(0);
    }
    else if(Pid > 0) {			//ESTAMOS NO PAI
      continue;
    }
    else if(Pid == -1 ) {		//ERRO NA CRIACAO DO PROCESSO FILHO
      printf(ERROR_FORK);
    }
  }
  
  times = 0;
  while(Wret = wait(&status) > 0){	//ESPERA PELA MORTE DOS FILHOS
    Pid = children[times++];
    printf("Processo %d terminou a %d\n", Pid, Wret);
  }

  gettimeofday(&t_end,NULL);

  t_duration.tv_sec = t_end.tv_sec - t_start.tv_sec;
  t_duration.tv_usec = t_end.tv_usec - t_start.tv_usec;

  printf("Tempo de execução : %ld.%4ld segundos\n", t_duration.tv_sec, t_duration.tv_usec);
  
  return 0;
}

