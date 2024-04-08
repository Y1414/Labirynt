#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



#include "read.h"
#include "movement.h"
#include "neighbours.h"


void instructions (int start, int width, int end, FILE*in, FILE*out){
    int current = start;
    char ways[4] = {check_up(current, in, width), check_right(current, in), check_down(current, in, width), check_left(current, in)};
    char direction = 0;
    direction = choose_direction(ways, direction);
    char new_direction;
    int sum = -1;

    while(current != end)
    {
        char ways[4] = {check_up(current, in, width), check_right(current, in), check_down(current, in, width), check_left(current, in)};

        fseek(in, current, SEEK_SET);

        
        if ((new_direction = choose_direction(ways, direction)) != direction){
            fprintf(out, "FORWARD %d\n", sum+1);
            if (direction - new_direction == -1 ||direction - new_direction == 3)
                fprintf(out, "TURNRIGHT\n");
            else if (direction - new_direction == 1 || direction - new_direction == -3)
                fprintf(out, "TURNLEFT\n");
            direction = choose_direction(ways, direction);
            
            sum=0;
        }else{
            sum++;
        }
        current = move_forward(current, direction, width);
    }
    fprintf(out, "FORWARD %d\n", sum+1);
}