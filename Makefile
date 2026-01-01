all:
	gcc -Wall -Wextra -g -o main main.c `sdl2-config --cflags --libs`
