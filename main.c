#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <SDL2/SDL.h>
#include <string.h>

char *replace_format(char *in){
	if (in == NULL) return NULL;

    char *dot = strrchr(in, '.');
    long base_len;

    if (dot) {
        base_len = dot - in; 
    } else {
        base_len = strlen(in); 
    }

    char *new_str = (char *)malloc(sizeof(char) * base_len + 5);

    if (new_str == NULL) {
        return NULL; // Falha na alocação de memória
    }

    strncpy(new_str, in, base_len);
    new_str[base_len] = '\0'; 
    strcat(new_str, ".ppm");

    return new_str;
}

int main(int argc, char** argv){

	printf("%d pid: %d\n", argc, getpid());

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Erro ao inicializar SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
	if (argc != 2) exit(EXIT_FAILURE); 
	int wait_fork = 0;
	pid_t pid = fork();
	if (pid == 0){
		if ((execlp("python3", "python3", "image_parser.py", argv[1], NULL)) ==  -1) perror("PYTHON ERROR!");
	}

	else if (pid < 0) exit(EXIT_FAILURE);

	wait(&wait_fork);
	char* ppm = replace_format(argv[1]);
	FILE * f = fopen(ppm, "r");
	if (f == NULL) exit(EXIT_FAILURE);
	char *pthroaway = (char*)calloc(1000, sizeof(char));
	fgets(pthroaway, 1000, f);
	free(pthroaway);

	char *pdimensions = (char*)calloc(1000, sizeof(char));
	fgets(pdimensions, 1000, f); 

	int pwidth, pheight; 
	sscanf(pdimensions, "%d %d\n", &pwidth, &pheight);
	free(pdimensions); 
	SDL_Window * pwindow = SDL_CreateWindow("Image view", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, pwidth, pheight, 0);
	SDL_Surface * psurface = SDL_GetWindowSurface(pwindow);
	Uint32 color = 0;
	SDL_Rect pixel = (SDL_Rect){0, 0, 1, 1}; //Aqui é possível usar threads
	for (int y = 0; y < pheight; y++){
		for (int x = 0; x < pwidth; x++){
			Uint8 r, g, b;
			b = (char) fgetc(f);
			r = (char) fgetc(f);
			g = (char) fgetc(f);
			color = SDL_MapRGB(psurface->format, r, g, b); 
			pixel.x = x, pixel.y = y;
			SDL_FillRect(psurface, &pixel, color);
		}
	}
	fclose(f); 
	SDL_UpdateWindowSurface(pwindow);
	int app_running = 1;
	while(app_running){
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
				app_running = 0;
			}
			
		}
		SDL_Delay(100);
	}

	if (remove(ppm) != 0) {
        printf("Couldnt remove file!");
		return -1;
    }
	SDL_DestroyWindowSurface(pwindow); 
	SDL_DestroyWindow(pwindow);
	SDL_Quit();
	free(ppm);
	return 0;
}