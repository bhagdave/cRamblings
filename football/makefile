CC=gcc
CFLAGS=-I.
DEPS=team.h score.h league.h season.h menu.h
OBJ=testteam.o league.o team.o score.o menu.o season.o

%.o : %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

testteam : $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core
