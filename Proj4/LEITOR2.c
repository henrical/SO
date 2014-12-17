#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h> 
#include <string.h>

#define ERROR_LOCK "LEITOR2 - Erro a obter LOCK!\n"
#define ERROR_UNLOCK "LEITOR2 - Erro a libertar LOCK!\n"

#define THREAD_ERROR "ERROR NA CRIACAO DA THREAD"
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

int treturns[THREAD_NUM] = {0, 0, 0};

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
  
  int times = LINES_NUM;
  int *temp = (int*)args;
  int file_pos = temp[0], return_index = temp[1];	
  int i, bool = 1;						
  
  char *buffer = (char*)malloc(CHARS*sizeof(char)), 
       *match = (char*)malloc(CHARS*sizeof(char));
  
  int file = open(files[file_pos], O_RDONLY, S_IRUSR|S_IROTH);
  
  if( file > 0){
	  int lock = flock(file, LOCK_SH);
	   
	  if(lock < 0) 
	      printf(ERROR_LOCK);
	  
	  int Ssize = read(file, buffer, CHARS);			 
	  
	  for(i = 0; i < MAX_STRING_POS; i++) 
	  {			
		if(strcmp(strings[i], buffer) == 0)
		{ 
			bool = 0;
			break;
		}
	  }
	 
	  if(Ssize == CHARS && bool == 0){                                     
												 
	   strcpy(match, buffer);  
		
	   while(times-- != 0)
	   {
		Ssize = read(file, buffer, CHARS);  
		if(strcmp(buffer, match) != 0 || Ssize != CHARS) 
			break;
	   }
	   
	      lock = flock(file, LOCK_UN);
	      if(lock < 0)
		printf(ERROR_UNLOCK);
	      
	      free(buffer);
	      free(match);
	      close(file);
	      
	      if(times != 0) 			 
	      {
		treturns[return_index] = -1;
		return NULL;
		
	      }
	      else return NULL;
	  } 
	  else
	  {	
	      lock = flock(file, LOCK_UN);
	      if(lock < 0) 		
		printf(ERROR_UNLOCK);
	      
	      free(buffer);
	      free(match);
	      
	      treturns[return_index] = -1;
	      return NULL;
	  }
	}
	else
	  {
	      free(buffer);
	      free(match);
	      treturns[return_index] = -1;
	      return NULL;
	  } 
}

int main(){
  struct timeval tvstart, tvend, tvduration;
  unsigned long int duration;
  int thread_err, i;
  pthread_t tid[THREAD_NUM];
  
  gettimeofday(&tvstart,NULL);
  srand((tvstart.tv_sec * 1000)+(tvstart.tv_usec / 1000));
  
  for(i=0; i < THREAD_NUM; i++){
    int *buffer = (int*)malloc(2*sizeof(int));
    buffer[0] = random_number(THREAD_NUM); buffer[1] = i;
    
    if(!pthread_create(&tid[i], 0, ReadFromFile, (void*)buffer)){
      printf ("Criada a tarefa %d\n", tid[i]);
    }
    else{
      printf(THREAD_ERROR);
      exit(1);}
  }
  
   for (i=0; i < THREAD_NUM; i++){
    pthread_join (tid[i], NULL);
    printf ("Terminou a tarefa %ld e devolveu %d\n", tid[i], treturns[i]);
   }
   
     gettimeofday(&tvend,NULL);
  
	tvduration.tv_sec = tvend.tv_sec - tvstart.tv_sec;
	tvduration.tv_usec = tvend.tv_usec - tvstart.tv_usec;
	duration = tvduration.tv_sec * 1000000 + tvduration.tv_usec;
    printf("Tempo de execução : %ld microsegundos\n", duration);
   
  return 0;
}