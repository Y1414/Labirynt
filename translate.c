#include <stdio.h>
#include <stdint.h>

char*  translate(FILE*in ) {
    char* filename = "maze.txt";
    FILE * out = fopen(filename, "w");
    typedef struct 
    {
        uint32_t part1;
        uint32_t part2;
        uint32_t part3;
    } Reserved;
    
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
                //line_counter = 0;
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
