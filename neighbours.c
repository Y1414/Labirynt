#include <stdio.h> 
#include <stdlib.h>   
#include <stdint.h>    
    
int check_right (int current, FILE*in){   
    char character; 
    fseek(in, current + 1, SEEK_SET); 
    character = fgetc(in); 
    return character;
}
int check_left (int current, FILE*in){   
    char character; 
    fseek(in, current - 1, SEEK_SET); 
    character = fgetc(in); 
    return character;
}
int check_up (int current, FILE*in, int width){   
    char character;
    fseek(in, current - width - 1, SEEK_SET); 
    character = fgetc(in);
    return character;
}
int check_down (int current, FILE*in, int width){   
    char character; 
    fseek(in, current + width +1, SEEK_SET);
    character = fgetc(in); 
    return character;
}

int count_walls(int current, FILE*in, int width){
    char ways[4] = {check_up(current, in, width), check_right(current, in), check_down(current, in, width), check_left(current, in)};
    char sum = 0;
    for (int i=0;i<4;i++){
        if (ways[i] == 'X' || ways[i] == '\n' || ways[i] == 'O')
            sum++;
    }   
    return sum;
}
int count_ways(int current, FILE*in, int width){
    char ways[4] = {check_up(current, in, width), check_right(current, in), check_down(current, in, width), check_left(current, in)};
    char sum = 0;
    for (int i=0;i<4;i++){
        if (ways[i] == ' ' || ways[i] == 'K')
            sum++;
    }   
    return sum;
}
