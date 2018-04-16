CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = uniq
OBJS = uniq.o readline.o
all : $(MAIN)

$(MAIN) : $(OBJS) readline.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

uniq.o : uniq.c readline.h
	$(CC) $(CFLAGS) -c uniq.c 

readline.o : readline.c
	$(CC) $(CFLAGS) -c readline.c

clean :
	rm *.o $(MAIN) core
