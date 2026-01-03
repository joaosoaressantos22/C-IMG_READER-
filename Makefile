all:
	gcc -Wall -Wextra -g -o main *.c `sdl2-config --cflags --libs`
