CC = gcc
G77 = gfortran
IDIR = ./include
CFLAGS = -I$(IDIR) -std=c99

EXE = bin/2.out bin/schrage bin/atof bin/direct bin/dataprocess bin/rejection5 bin/rejection4 bin/Mintegral bin/rwsin bin/backtoorigin bin/lyapunov bin/dla

all:bin/2.out bin/schrage bin/atof bin/direct bin/dataprocess bin/rejection5 bin/rejection4 bin/Mintegral bin/rwsin bin/backtoorigin bin/lyapunov bin/dla bin/sandbox bin/box bin/hpp bin/Markov bin/Markov_gas

bin/Markov_gas:obj/Markov_gas.o
	$(CC) obj/Markov_gas.o -o bin/Markov_gas $(CFLAGS)

bin/Markov:obj/Markov.o
	$(CC) obj/Markov.o -o bin/Markov $(CFLAGS)

bin/hpp:obj/hpp.o
	$(CC) obj/hpp.o -o bin/hpp $(CFLAGS)

bin/box:obj/box.o
	$(CC) obj/box.o -o bin/box $(CFLAGS)

bin/sandbox:obj/sandbox.o
	$(CC) obj/sandbox.o -o bin/sandbox $(CFLAGS)

bin/dla:obj/dla.o
	$(CC) obj/dla.o -o bin/dla $(CFLAGS)

bin/lyapunov:obj/lyapunov.o
	$(CC) obj/lyapunov.o -o bin/lyapunov $(CFLAGS)

bin/backtoorigin:obj/backtoorigin.o
	$(CC) obj/backtoorigin.o -o bin/backtoorigin $(CFLAGS)

bin/rwsin:obj/rwsin.o
	$(CC) obj/rwsin.o -o bin/rwsin $(CFLAGS)

bin/Mintegral:obj/Mintegral.o
	$(CC) obj/Mintegral.o -o bin/Mintegral $(CFLAGS)

bin/rejection4:obj/rejection4.o
	$(CC) obj/rejection4.o -o bin/rejection4 $(CFLAGS)

bin/rejection5:obj/rejection5.o obj/discreteCDF.o
	$(CC) obj/rejection5.o obj/discreteCDF.o -o bin/rejection5 $(CFLAGS)

bin/dataprocess:obj/dataprocess.o
	$(CC) obj/dataprocess.o -o bin/dataprocess

bin/direct:obj/direct.o obj/discreteCDF.o
	$(CC) obj/direct.o obj/discreteCDF.o -o bin/direct

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
