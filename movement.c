#include <stdio.h>
#include <stdlib.h>


int move_up (int current, int width){
    return current- width - 1;
}
int move_down (int current, int width){
    return current + width + 1;
}
int move_right (int current){
    return current + 1;
}
int move_left (int current){
    return current - 1;
}

int move_forward (int current, char direction, int width){
    switch (direction)
    {
    case 0:
        return move_up(current, width);
    case 1:
        return move_right(current);
    case 2:
        return move_down(current, width);
    case 3:
        return move_left(current);
    default:
        printf("direction error");
        exit(1);
    }
}


char choose_direction(char*ways, char direction){
    direction = (direction+2)%4;
    char new_direction;
    for (int i=0;i<4;i++){
        new_direction =i;
        if ((ways[i] == ' ' || ways[i] == 'K') && new_direction != direction){
            return new_direction;
        }
    }
    for (int i=0;i<4;i++){
        new_direction =i;
        if (ways[i] == 'O' && new_direction != direction){
            return new_direction;
        }
    }
    return direction;

}