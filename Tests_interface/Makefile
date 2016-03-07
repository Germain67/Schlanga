all: main

main:
	gcc `pkg-config --cflags gtk+-3.0` -o main clutter_interface.c `pkg-config --libs gtk+-3.0`

clean:
	rm -rf *.o main
