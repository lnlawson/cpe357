TARGET   = hencode
TARGET2  = hdecode
CC       = gcc
CCFLAGS  = -pedantic -Wall -Werror -ansi -g -lm -std=c99
OBJECTS  = hencode.o
OBJECTS2 = hdecode.o

all: $(TARGET) $(TARGET2)

$(TARGET):$(OBJECTS) 
	$(CC) $(CCFLAGS) -o $(TARGET) $(OBJECTS)

hencode.o: hencode.c hencode.h
	$(CC) -c $(CCFLAGS) hencode.c

$(TARGET2):$(OBJECTS2)
	$(CC) $(CCFLAGS) -o $(TARGET2) $(OBJECTS2)

hdecode.o: hdecode.c hdecode.h
	$(CC) -c $(CCFLAGS) hdecode.c


clean:
	rm -f $(TARGET) $(OBJECTS) $(TARGET2) $(OBJECTS2) 

recomp: clean all
