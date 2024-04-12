#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "translate.h"
#include "read.h"
#include "bfs.h"
#include "inverse.h"
#include "instructions.h"
#include "clear.h"

int main (int argc, char** argv ){

    if (argc < 2){
        printf("Podaj plik z labiryntem jako argument wywołania\n");
        return 1;
    }
    FILE*in;
    FILE*bin;
    char* filename = argv[1];
    char* maze_filename = "";

    if (strstr(filename, ".bin\0")){
        bin = fopen(filename, "rb+");
        if (bin == NULL){
            printf("Błąd w czytaniu pliku: %s", filename);
            return 1;
        }
        maze_filename = translate(bin, filename);
        in = fopen(maze_filename, "r+");
    }
    else if (strstr(filename, ".txt\0")){
        in = fopen(filename, "r+");
        if (in == NULL){
            printf("Błąd w czytaniu pliku: %s", filename);
            return 1;
        }
        bin = to_bin(in, filename);
    }
    else{
        printf("Nieznany format pliku\n");
        return 1;
    }
    
    char* instructions_sufix = "_instructions.txt";
    char * instructions_filename = filename;
    char *ptr = strrchr(instructions_filename, '.');
    strcpy(ptr, instructions_sufix);
    


    FILE* out = fopen(instructions_filename, "w");
    int start=0, end=0, width=0, len=0;

    read(&start, &end, &width, in);
    
    bfs(start, end, width, in);
    inverse(in);

    instructions(start, width, end, in, out, bin);
    clear(in);

    fclose(in);
    fclose(bin);
    return 0;
}