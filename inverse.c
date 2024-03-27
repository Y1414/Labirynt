  
#include <stdio.h>
#include <stdlib.h>

void inverse(FILE* in){
    rewind(in);
    char x;
    while ((x = fgetc(in)) != EOF)
    {
        if (x == '+'){
            fseek(in, -1 , SEEK_CUR);
            fputc(' ', in);
        }
        else if (x != 'X' && x != '\n' && x != 'K' && x != 'P' && x != 'O'){
            fseek(in, -1 , SEEK_CUR);
            fputc('O', in);
        }
    }
}