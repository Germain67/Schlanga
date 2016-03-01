all: main

#main:
#	gcc -o main interface.c `sdl-config --cflags --libs`

main: main.o plateau.o element.o snake.o
	gcc -o main main.o plateau.o element.o snake.o

plateau.o: plateau.c
	gcc -o plateau.o -c plateau.c

element.o: element.c
	gcc -o element.o -c element.c

snake.o: snake.c
	gcc -o snake.o -c snake.c
	
main.o: main.c plateau.h element.h snake.h
	gcc -o main.o -c main.c

clean:
	rm -rf *.o main
