#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "translate.h"
#include "read.h"
#include "bfs.h"
#include "inverse.h"
#include "ff.h"
#include "instructions.h"
#include "clear.h"

int main (){
    /*FILE* in = fopen("test.txt", "r+");
    FILE* map = fopen("map.txt", "w+");
    translate(in, map);*/

    clock_t poczatek = clock();
    //FILE* in = fopen("1024x1024.txt", "r+");
    FILE* bin = fopen("maze.bin", "rb");
    FILE * in = fopen(translate(bin), "r+");

    FILE* out = fopen("instuctions.txt", "w");
    int start=0, end=0, width=0, len=0;

    read(&start, &end, &width, in);
    
    bfs(start, end, width, in);
    inverse(in);

    instructions(start, width, end, in, out);

    fclose(in);
    clock_t koniec = clock();
    double duration = (double)(koniec - poczatek) / CLOCKS_PER_SEC;
    printf("Czas wykonania kodu: %.4f sekund\n", duration);
    return 0;
}