CC=gcc
CFLAGS=-I.
DEPS=menu.h item.h
OBJ=music.o menu.o item.o

%.o : %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

music : $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core
