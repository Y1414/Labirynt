#include <stdio.h>


void clear (FILE*in){
    rewind(in);
    char x;
    while ((x = fgetc(in)) != EOF)
    {
        if (x == 'O'){
            fseek(in, -1 , SEEK_CUR);
            fputc(' ', in);
        }    
    }
}