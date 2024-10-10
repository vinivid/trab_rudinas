CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -fsanitize=address -lm 
OBJS = lista_encadeada.c lista_adjacencia.c menor_dist.c main.c subconjuntos.c dinamica.c 
DEPS = lista_encadeada.h lista_adjacencia.h menor_dist.h subconjuntos.h dinamica.h

all: $(OBJS) $(DEPS)
	$(CC) $(CFLAGS) $(OBJS) -o koala

run:
	./koala 

clean:
	rm koala
