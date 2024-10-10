CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -fsanitize=address -lm 
OBJS = lista_encadeada.c lista_adjacencia.c menor_dist.c main.c 
DEPS = lista_encadeada.h lista_adjacencia.h menor_dist.h 

HOB = dp.c held_encadeada.c held_lista.c subconjuntos.c 
DH = held_lista.h held_encadeada.h subconjuntos.h 

all: $(OBJS) $(DEPS)
	$(CC) $(CFLAGS) $(OBJS) -o tsp

otimizado: $(DH)
	$(CC) $(CFLAGS) $(HOB) -o tsp_oti

run:
	./koala 

clean:
	rm koala
