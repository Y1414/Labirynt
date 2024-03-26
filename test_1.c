#include <stdio.h>

#include "read.h"
#include "clear.h"
#include "bfs.h"
#include "inverse.h"
#include "instructions.h"

int main (){
    FILE* in = fopen("300_20.txt", "r+");
    FILE* out = fopen("instuctions.txt", "w");
    int start=0, end=0, width=0, len=0;
    read(&start, &end, &width, in);

    bfs(start, end, width, in);
    inverse(in);
    instructions(start, width, end, in, out);


    clear(in);
    fclose(in);

    return 0;
}