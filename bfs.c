#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "read.h"
#include "neighbours.h"
#include "movement.h"
#include "inverse.h"


int is_end (char* ways){
    for (int i=0;i<4;i++){
        if(ways[i] == 'K')
            return 1;
    }
    return 0;
}
char select_char (char direction){
    if (direction == 0)
        return '.';
    if (direction == 1)
        return '<';
    if (direction == 2)
        return '^';
    if (direction == 3)
        return '>';
}

int is_start(char*ways){
    for (int i=0;i<4;i++){
        if(ways[i] == 'P')
            return 1;
    }
    return 0;
}
char get_direction(char current){
    if (current == '.')
        return 2;
    if (current == '^')
        return 0;
    if (current == '>')
        return 1;
    if (current == '<')
        return 3;
}


void translate_path (int start, int width,int end, FILE* in){
    char direction = 0;
    int current = start;
    while(1)
    {

        char ways[4] = {check_up(current, in, width), check_right(current, in), check_down(current, in, width), check_left(current, in)};
        if (is_start(ways)){
            fputc(' ', in);
            break;
        }
        fseek(in, current, SEEK_SET);

        char current_char = fgetc(in);
        direction = get_direction(current_char);
        fseek(in, -1, SEEK_CUR);
        if (current == end)
            fputc('K', in);
        else
            fputc('+', in);
        current = move_forward(current, direction, width); 
    }   
      
}

void bfs (int start, int end, int width, FILE*in){
    stack_t queue = init_stack();
    queue = put_on_back(start, -1, queue);
    int current;
    while (1){
        current = stack_head(queue);
        char ways[4] = {check_up(current, in, width), check_right(current, in), check_down(current, in, width), check_left(current, in)};
        queue = stack_pop(queue);
        for (int i=0;i<4;i++){
            if(ways[i] == ' ' || ways[i] == 'K'){
                int new_pos = move_forward(current, i, width);
                fseek(in, new_pos, SEEK_SET);
                fputc(select_char(i), in);
                queue = put_on_back(new_pos, current, queue);
            }
        }
        if (is_end(ways))
            break;
    }
    free_stack(queue);
    translate_path(end, width,end, in);
}