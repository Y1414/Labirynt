#include <stdio.h>

void clear (FILE*in){
    rewind(in);
    char x;
    while ((x = fgetc(in)) != EOF)
    {
        if (x == 'O' || x == '.' || x == '^' || x == '>' || x == '<' ){
            fseek(in, -1 , SEEK_CUR);
            fputc(' ', in);
        }    
    }
}