#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct 
    {
        uint32_t part1;
        uint32_t part2;
        uint32_t part3;
    } Reserved;

char*  translate(FILE*in ) {
    char* filename = "maze.txt";
    FILE * out = fopen(filename, "w");
    
    
    uint32_t id;
    uint8_t escape;
    uint16_t columns;
    uint16_t lines;
    uint16_t entry_x;
    uint16_t entry_y;
    uint16_t exit_x;
    uint16_t exit_y;
    Reserved reserved;
    uint32_t counter;
    uint32_t solution_offset;
    uint8_t separator;
    uint8_t wall;
    uint8_t path;

    fread(&id, sizeof(id), 1, in);
    fread(&escape, sizeof(escape), 1, in);
    fread(&columns, sizeof(columns), 1, in);
    fread(&lines, sizeof(lines), 1, in);
    fread(&entry_x, sizeof(entry_x), 1, in);
    fread(&entry_y, sizeof(entry_y), 1, in);
    fread(&exit_x, sizeof(exit_x), 1, in);
    fread(&exit_y, sizeof(exit_y), 1, in);
    fread(&reserved, sizeof(reserved), 1, in);
    fread(&counter, sizeof(counter), 1, in);
    fread(&solution_offset, sizeof(solution_offset), 1, in);
    fread(&separator, sizeof(separator), 1, in);
    fread(&wall, sizeof(wall), 1, in);
    fread(&path, sizeof(path), 1, in);

    uint8_t separator2;
    uint8_t value;
    uint8_t count;

    int line_counter = 0;
    int start = columns * (entry_y -1)  + (entry_x-1);
    int end = columns * (exit_y -1)  + (exit_x-1);

    for (int i=0;i<counter;i++){
        fread(&separator2, sizeof(separator2), 1, in);
        fread(&value, sizeof(value), 1, in);
        fread(&count, sizeof(count), 1, in);
        for(int j=0;j<=count;j++){
            if (line_counter % (int)columns == 0 && line_counter != 0 ){
                fputc('\n', out);
            }
            if (line_counter == start)
                fputc('P', out);
            else if (line_counter == end)
                fputc('K', out);
            else
                fputc((char)value, out);

            line_counter++;
        }
    }
    
    fclose(in);
    fclose(out);

    return filename;
}

void to_bin(FILE* in){

    FILE*out = fopen("maze.bin", "w");

    uint32_t id = 0x52524243;
    uint8_t escape = 0x1B;
    uint16_t columns = 1;
    uint16_t lines = 1;
    uint16_t entry_x = 0;
    uint16_t entry_y = 0;
    uint16_t exit_x = 0;
    uint16_t exit_y=  0;
    Reserved reserved;
    memset(&reserved, 0, sizeof(reserved));
    uint32_t counter = 0;
    uint32_t solution_offset = 1;
    uint8_t separator = '#';
    uint8_t wall = 'X';
    uint8_t path = ' ';
    uint8_t value = ' ';
    uint8_t count = 0;

    char c;
    int x = 0;
    int y = 1;
    char current_value;

    
    fseek(out, 40 - 3, SEEK_SET);

    while((c = fgetc(in)) != EOF){
        if (c == '\n'){
            lines++;
            y++;
            if (columns == 1){
                columns = x;
            }
            x = 0;
        }
        
        else if (c == 'P'){
            entry_x = x;
            entry_y = y;
            c = ' ';
        }
        else if (c == 'K'){
            exit_x = x;
            exit_y = y;
            c = ' ';
        }

        if (c == ' ' || c == 'X'){
            if (c != value || count == 255){
                fwrite(&separator, sizeof(separator), 1, out);
                fwrite(&value, sizeof(value), 1, out);
                fwrite(&count, sizeof(count), 1, out);
                value = c;
                count = 0;
                counter++;
            }
            else{
                count ++;
            }
        }


        x++;
    }
    fwrite(&separator, sizeof(separator), 1, out);
    fwrite(&value, sizeof(value), 1, out);
    fwrite(&count, sizeof(count), 1, out);


    rewind(in);
    rewind(out);
    fwrite(&id, sizeof(id), 1, out);
    fwrite(&escape, sizeof(escape), 1, out);
    fwrite(&columns, sizeof(columns), 1, out);
    fwrite(&lines, sizeof(lines), 1, out);
    fwrite(&entry_x, sizeof(entry_x), 1, out);
    fwrite(&entry_y, sizeof(entry_y), 1, out);
    fwrite(&exit_x, sizeof(exit_x), 1, out);
    fwrite(&exit_y, sizeof(exit_y), 1, out);
    fwrite(&reserved, sizeof(reserved), 1, out);
    fwrite(&counter, sizeof(counter),1 , out);
    fwrite(&solution_offset, sizeof(solution_offset),1 , out);
    fwrite(&separator, sizeof(separator), 1, out);
    fwrite(&wall, sizeof(wall), 1, out);
    fwrite(&path, sizeof(path), 1, out);
    

    fclose(out);
}