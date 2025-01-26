CC = gcc
CFLAGS = -Wall -g
OBJ = main.o funcoes.o
EXEC = gerenciador_tarefas

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c funcoes.h
	$(CC) $(CFLAGS) -c main.c

funcoes.o: funcoes.c funcoes.h
	$(CC) $(CFLAGS) -c funcoes.c

clean:
	rm -f $(OBJ) $(EXEC)

