#include <stdio.h>
#include <stdbool.h>

#include "neighbours.h"
#include "movement.h"
#include "corridors.h"

void fill_path (int start, int width, FILE* in){
    char direction = 0;
    int current = start;
    char ways[4] = {check_up(current, in, width), check_right(current, in), check_down(current, in, width), check_left(current, in)};
    direction = choose_direction(ways, direction);  
    while(count_walls(current, in, width) > 2)
    {
        char ways[4] = {check_up(current, in, width), check_right(current, in), check_down(current, in, width), check_left(current, in)};
        fseek(in, current, SEEK_SET);
        char x;
        if ((x = fgetc(in)) == ' '){
            fseek(in, -1, SEEK_CUR);
            fputc('X', in);
        }
        if (check_if_corridor(ways) == false){
            direction = choose_direction(ways, direction);
        }
        current = move_forward(current, direction, width);
    }      
}


bool ff (FILE* in, int width){
    rewind(in);
    int current = 0;
    bool found = false;
    char current_char= ' ';
    
    while (current_char != EOF){
        fseek(in, current, SEEK_SET);
        if ((current_char = fgetc(in)) == ' '){
            if(count_walls(current, in, width) == 3){
                fill_path(current, width, in);
            }
        }
        current++;
    } 
    return found;
}


