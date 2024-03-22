#include <stdio.h>

#include "ff.h"
#include "read.h"
#include "clear.h"

int main (){
    FILE* in = fopen("300_20.txt", "r+");
    int start=0, end=0, width=0, len=0;
    read(&start, &end, &width, in);

    
    //while(ff(in, width));

    clear(in);
    fclose(in);

    return 0;
}