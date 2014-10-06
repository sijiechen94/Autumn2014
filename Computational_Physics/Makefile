CC = gcc
G77 = gfortran
IDIR = ./include
CFLAGS = -I$(IDIR) -std=c99 -lm

all:bin/2.out bin/schrage bin/randomz bin/atof

bin/randomz:src/randomz.f95
	$(G77) src/randomz.f95 -o bin/randomz

bin/atof:obj/atof.o
	$(CC) obj/atof.o -o bin/atof $(CFLAGS)

bin/2.out:obj/2.o
	$(CC) obj/2.o -o bin/2.out $(CFLAGS)

bin/schrage:obj/1.o obj/test1.o
	$(CC) obj/1.o obj/test1.o -o bin/schrage $(CFLAGS)
	 
obj/%.o:src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f obj/*.o bin/*
