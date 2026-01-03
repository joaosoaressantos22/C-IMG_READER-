#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"

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

void help(void){
    printf("To run the image viewer you must run viewercapi (FILE_NAME OR DIRECTORY/FILE_NAME)\n");
    printf("It's also optional to resize the image, just set the witdth and height after the FILE_NAME, remember that widht and height MUST BE INTEGERS!\n ");
}
