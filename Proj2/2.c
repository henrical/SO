/*	ESCRITOR-PAI FUNCOES fork() wait(status) execlp(path, file, args)
 * 	
 * 	ESSENCIA-> FAZ FORK(), GUARDA PID RESULTANTE, 
 * 	ESPERA FILHOS, FAZ OUTPUT TEMPO DE EXECUCAO
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define ERROR_FORK "ERRO! Processo-filho não foi criado.\n"
#define MAX 10
#define PATH "./ESCRITOR"
#define EXECUTABLE "ESCRITOR"

int main(){
  
  time_t start = time(&start), end;	//INICIALIZA VARIAVEL CONTAGEM DE INICIO DE PROGRAMA
  int times = 0, status = 0;		//QTD DE CICLOS - TIPO DE RETORNO DE WAIT() 
  pid_t children[MAX];			//ARRAY COM PIDs DOS VARIOS P-FILHOS
  pid_t Pid, Wret;			//PID = PROCESS ID - Wret = 'valor retornado por Wait()'
  
  
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
  
  end = time(&end);			//INICIALIZA VARIAVEL CONTAGEM DE FIM DE PROGRAMA
  printf("Tempo de execução : %d segundos\n", (int)(end - start));
  
  return 0;
}

