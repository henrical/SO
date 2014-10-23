all: ESCRITOR LEITOR

ESCRITOR: ESCRITOR.o writer.o
	gcc -o ESCRITOR ESCRITOR.o writer.o

ESCRITOR.o: ESCRITOR.c
	gcc -g -c ESCRITOR.c
	
LEITOR: LEITOR.o reader.o
	gcc -o LEITOR LEITOR.o reader.o
	
LEITOR.o: LEITOR.c
	gcc -g -c LEITOR.c
	
reader.o: reader.c
	gcc -g -c reader.c
	
writer.o: writer.c
	gcc -g -c writer.c