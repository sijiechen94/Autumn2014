CC = gcc
G77 = gfortran
IDIR = ./include
CFLAGS = -I$(IDIR) -std=c99

all:bin/2.out bin/schrage bin/atof bin/direct bin/dataprocess bin/rejection5 bin/rejection4 bin/Mintegral bin/rwsin bin/backtoorigin

bin/backtoorigin:obj/backtoorigin.o
	$(CC) OBJ/backtoorigin.o -o bin/backtoorigin $(CFLAGS)

bin/rwsin:obj/rwsin.o
	$(CC) OBJ/rwsin.o -o bin/rwsin $(CFLAGS)

bin/Mintegral:obj/Mintegral.o
	$(CC) OBJ/Mintegral.o -o bin/Mintegral $(CFLAGS)

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
