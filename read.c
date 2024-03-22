#include <stdio.h>
#include <stdlib.h>

void read (int*start, int*end, int*width, FILE *in){
    int len = 0;
    char current_char;
    while ((current_char = fgetc(in)) != EOF)
    {
        len++;
        switch (current_char)
        {
        case '\n':
            if (*width == 0)
                *width = len-1;
            break;
        case 'P':
            *start = len-1;
            break;
        case 'K':
            *end = len-1;
            break;
        case 'X':
            break;
        case ' ':
            break;
        case 'O':
            break;
        default:
            printf("błędny format pliku");
            printf("%c ", current_char);
            exit(1);
        }

    }
    rewind(in);
}