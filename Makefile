all: 
	main

main:
	gcc -o main interface.c `sdl-config --cflags --libs`

clean:
	rm -rf *.o main

