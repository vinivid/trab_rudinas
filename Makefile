CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -fsanitize=address
OBJS = lista_encadeada.c lista_adjacencia.c main.c
DEPS = lista_encadeada.h lista_adjacencia.h

all: $(OBJS) $(DEPS)
	$(CC) $(CFLAGS) $(OBJS) -o koala

run:
	./koala 

clean:
	rm koala
