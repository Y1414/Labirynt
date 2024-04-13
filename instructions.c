#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "read.h"
#include "movement.h"
#include "neighbours.h"

char get_direction_char(char direction){
    if (direction == 0)
        return 'N';
    if (direction == 1)
        return 'E';
    if (direction == 2)
        return 'S';
    if (direction == 3)
        return 'W';
    printf("Nieznany kierunek \n");
    exit(1);    
}
char get_direction_int(char direction){
    if (direction == 'N')
        return 0;
    if (direction == 'E')
        return 1;
    if (direction == 'S')
        return 2;
    if (direction == 'W')
        return 3;
    printf("Nieznany kierunek \n");
    exit(1);    
}

int make_step(int width, int current, char counter, char direction, FILE*in){
    for(int i=0;i<=counter;i++){
        fseek(in, current, SEEK_SET);
        if (fgetc(in) == ' '){
            fseek(in, -1, SEEK_CUR);
            fputc('+', in);
        }
        current = move_forward(current, direction, width);
        
    }
    return current;
}


void instructions (int start, int width, int end, FILE*in, FILE*out, FILE*bin){
    int current = start;
    char ways[4] = {check_up(current, in, width), check_right(current, in), check_down(current, in, width), check_left(current, in)};
    char direction = 0;
    direction = choose_direction(ways, direction);
    char new_direction;
    int sum = -1;

    uint32_t id;
    uint32_t counter = 0;
    uint32_t solution_offset = 0;
    uint32_t steps = 1;
    uint8_t direction_bin;
    uint8_t count;

    fseek(bin , 29, SEEK_SET);

    fread(&counter, sizeof(counter), 1, bin);

    solution_offset = counter*3 + 40;

    fwrite(&solution_offset, sizeof(solution_offset), 1, bin);

    fseek(bin , solution_offset, SEEK_SET);
    fread(&id, sizeof(id), 1, bin);

    fwrite(&steps,sizeof(steps) , 1, bin);


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

            direction_bin = get_direction_char(direction);
            count = sum;

            fwrite(&direction_bin, sizeof(direction_bin), 1, bin);
            fwrite(&count, sizeof(count), 1, bin);
            steps++;

            direction = choose_direction(ways, direction);
            
            sum=0;
        }else{
            sum++;
        }
        current = move_forward(current, direction, width);
    }
    fprintf(out, "FORWARD %d\n", sum+1);
    direction_bin = get_direction_char(direction);
    count = sum;
    fwrite(&direction_bin, sizeof(direction_bin), 1, bin);
    fwrite(&count, sizeof(count), 1, bin);
    fseek(bin , solution_offset, SEEK_SET);
    fread(&id, sizeof(id), 1, bin);
    fwrite(&steps,sizeof(steps) , 1, bin);

    fclose(out);
}

void read_solution (FILE*txt, FILE*bin, int start, int width){

    char solution_offset_position = 33;
    uint32_t solution_offset;
    uint32_t id;
    uint32_t steps;
    uint8_t direction_bin;
    uint8_t counter;
    char direction;
    int current = start;

    fseek(bin , solution_offset_position, SEEK_SET);
    fread(&solution_offset, sizeof(solution_offset), 1, bin);
    fseek(bin, solution_offset, SEEK_SET);
    fread(&id, sizeof(id), 1, bin);
    if (id != 0x52524243){
        printf("Nie znaleziono rozwiązania na solution offset\n");
        exit(1);
    }
    fread(&steps, sizeof(steps), 1, bin);
    
    for (int i=0;i<(int)steps;i++){
        fread(&direction_bin, sizeof(direction_bin), 1, bin);
        fread(&counter, sizeof(counter), 1, bin);
        direction = get_direction_int(direction_bin);

        current = make_step(width, current, counter, direction, txt);
    }

}