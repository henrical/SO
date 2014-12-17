#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h> 
#include <string.h>

#define THREAD_ERROR "LEITOR3 - ERRO NA CRIACAO DA THREAD"
#define T_JOIN_ERROR "LEITOR3 - Erro a fazer join de thread!\n"
#define ERROR_LOCK "LEITOR3 - Erro a obter LOCK!\n"
#define ERROR_UNLOCK "LEITOR3 - Erro a libertar LOCK!\n"
#define LSEEK_ERROR "LEITOR3 - Erro a procurar linha!\n"

#define THREAD_NUM 3
#define MAX_STRING_POS 10
#define MAX_FILE_POS 5
#define LINES_NUM 1024
#define CHARS 10

int random_number(int max)  
{
  int result;
  result = (rand() % max);
  return result;
}

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
  
void *ReadFromFile(void *args){
  
  int *temp = (int*)args;
  // 0->N LINHAS 1->POS RETORNO DE RESULTADO 3-> FD ACTUAL
  int times = temp[0], return_index = temp[1], file = temp[2];	
  int i, bool = 1;						
  
  char *buffer = (char*)malloc(CHARS*sizeof(char)), 
       *match = (char*)malloc(CHARS*sizeof(char));
  
       
	int jump = LINES_NUM/THREAD_NUM;
	jump = jump * 10 * return_index;
	printf("%d %d\n", jump, return_index);
	
	int lseekerr = lseek(file, jump,SEEK_SET);
	
	if(lseekerr < 0)
	printf(LSEEK_ERROR);
	
	int Ssize = read(file, buffer, CHARS);			 
	
	for(i = 0; i < MAX_STRING_POS; i++) 
	{			
	    if(strcmp(strings[i], buffer) == 0)
	    { 
		bool = 0;
		break;
	    }
	}
	
	if(Ssize == CHARS && bool == 0)
	{
	  strcpy(match, buffer);  
	  
	  while(times-- != 0)
	  {
	    Ssize = read(file, buffer, CHARS);  
	    if(strcmp(buffer, match) != 0 || Ssize != CHARS) 
		    break;
	  }
	  
	  free(buffer);
	  free(match);
	  
	  if(times > 0) 			 
	  {
	    temp[return_index+3] = -1;
	    return NULL;	
	  }
	  else return NULL;
	} 
	else
	{
	free(buffer);
	free(match);
	
	temp[return_index+3] = -1;
	return NULL;
	}
}

int main(int argc, char *argv[]){
  struct timeval tvstart, tvend, tvduration;
  unsigned long int duration;
  int thread_err, i, file_pos;
  int *buffer = (int*)malloc((3+THREAD_NUM)*sizeof(int));
  pthread_t tid[THREAD_NUM];
  
  gettimeofday(&tvstart,NULL);
  srand((tvstart.tv_sec * 1000)+(tvstart.tv_usec / 1000));
  
  if(argc == 2)
    file_pos = atoi(argv[1]);
  else
    file_pos = random_number(MAX_FILE_POS);
  
  int file = open(files[file_pos], O_RDONLY, S_IRUSR|S_IROTH);
  
  int lock = flock(file, LOCK_SH);
   if(lock < 0) 
	printf(ERROR_LOCK);
   
   
  for(i=3; i < THREAD_NUM; i++)
    buffer[i] = 0;
  
  buffer[2] = file;
  
  //THREAD CREATES
  for(i=0; i < THREAD_NUM; i++){
    buffer[0] = LINES_NUM/THREAD_NUM; buffer[1] = i; 
    //Acerto das linhas da ultima thread
    if(i == THREAD_NUM-1)
      buffer[0] += LINES_NUM % THREAD_NUM;
    
    if(!pthread_create(&tid[i], 0, ReadFromFile, (void*)buffer))
      printf ("Criada a tarefa %d\n", tid[i]);
    else{
      printf(THREAD_ERROR);
      exit(1);
    }
  }
  
  //THREAD JOINS
  int state = 0;
   for (i=0; i < THREAD_NUM; i++){
    if(pthread_join (tid[i], NULL) < 0)
      printf(T_JOIN_ERROR);
    
    if(buffer[i+3] == -1)
      state = -1;
   }
  printf ("Estado do ficheiro: %d\n", state);
   
  lock = flock(file, LOCK_UN);
  if(lock < 0) 
    printf(ERROR_LOCK);
    
  
    gettimeofday(&tvend,NULL);
  
  tvduration.tv_sec = tvend.tv_sec - tvstart.tv_sec;
  tvduration.tv_usec = tvend.tv_usec - tvstart.tv_usec;
  duration = tvduration.tv_sec * 1000000 + tvduration.tv_usec;
  printf("Tempo de execução : %ld microsegundos\n", duration);
   
  return 0;
}