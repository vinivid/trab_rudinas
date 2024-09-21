CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJS = main.c ls_du_encadeada.c 

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o koala

run:
	./koala 

clean:
	rm koala
