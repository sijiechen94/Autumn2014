CC = cc
IDIR = ./include
CFLAGS = -I$(IDIR)

all:./bin/1.out ./bin/2.out

./bin/1.out:obj/1.o obj/test1.o
	gcc obj/1.o obj/test1.o -o ./bin/1.out

./bin/2.out:obj/2.o
	gcc obj/2.o -o ./bin/2.out

obj/%.o:src/%.c
	gcc -c -o $@ $< $(CFLAGS)

clean:
	rm -f obj/*.o bin/*
