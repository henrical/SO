/*
 * LEITOR - LE UMA CADEIA DE CARATERES DE UMA FICHEIRO ALEATORIO
 */
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h> 

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

  int random_number(int max)  //gera numeros aleatorios entre 0 e max
{
  int result;
  srand(time(NULL));
  result = (rand() % max);
  return result;
}

  
int ReadFromFile(){
  int times = 1024; 				//quantidade de escritas a realizar
  int file_pos = random_number(5);		//posicao do array files a utilizar
  int i, bool = 1;						//bool > comparacao entre primeira linha e array strings
  
  char *buffer = (char*)malloc(10*sizeof(char)), 
       *match = (char*)malloc(10*sizeof(char));
  
  int file = open(files[file_pos], O_RDONLY, S_IRUSR|S_IROTH);	 //O_RDONLY - modo de acesso:leitura
																	                               //S_IRUSR - permissao de Read para dono do ficheiro
																	                               //S_IROTH - permissao de Read para outros utilizadores
  
  int Ssize = read(file, buffer, 10);			 //le primeira linha e copia para buffer(10 caracteres)
  
  for(i = 0; i < 10; i++) //verifica se a linha lida é uma das linhas permitidas
  {			
    if(strcmp(strings[i], buffer) == 0)
    { 
		  bool = 0;
		  break;
    }
	}
  
  if(file > 0 && Ssize == 10 && bool == 0){  // (file > 0) -> testa se o open() do ficheiro nao deu erro
                                             // Ssize sao o numero de bytes lidos na linha, têm de ser 10
                                             // bool é zero quando a linha esta efectivamente no array de strings permitidas
   strcpy(match, buffer);  //copia primeira linha do ficheiro para comparacao
    
   while(times-- != 0)
   {  // 1024 loops
      Ssize = read(file, buffer, 10);  //copia a nova linha para o buffer
      if(strcmp(buffer, match) != 0 || Ssize != 10) //compara uma linha com a 1ª e se o numero de bytes lidos foi 10. Se alguma das condiçoes fallhar o ciclo termina
	      break;
   }
    
    free(buffer);
    free(match);
    
    if(times != 0) 			 // se nao tiver lido 1024 linha ou ficheiro estiver errado termina com -1
      return -1;
    else
      return 0;
  }
    
      
  else
  {
    free(buffer);
    free(match);
    return -1;
  } 
  
}
