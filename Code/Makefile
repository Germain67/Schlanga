all: main_sdl

#main: main.o plateau.o element.o snake.o jeux.o IA.o
#	gcc -o main main.o plateau.o element.o snake.o jeux.o IA.o

main_sdl: main_sdl.o plateau.o element.o snake.o jeux_test.o IA.o
	gcc `sdl-config --cflags --libs` main_sdl.o plateau.o element.o snake.o jeux_test.o IA.o -o main_sdl

plateau.o: plateau.c
	gcc -o plateau.o -c plateau.c

element.o: element.c
	gcc -o element.o -c element.c

snake.o: snake.c
	gcc -o snake.o -c snake.c

#jeux.o: jeux.c
#	gcc -o jeux.o -c jeux.c

jeux_test.o: jeux_test.c
	gcc -o jeux_test.o -c jeux_test.c

IA.o: IA.c
	gcc -o IA.o -c IA.c
	
#main.o: main.c plateau.h element.h snake.h jeux.h IA.h
#	gcc -o main.o -c main.c

main_sdl.o: interface_sdl.c plateau.h element.h snake.h jeux.h IA.h
	gcc -c `sdl-config --cflags --libs` interface_sdl.c -o main_sdl.o 

clean:
	rm -rf *.o main main_sdl
