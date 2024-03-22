int check_down (int current, FILE*in, int width);
int check_up (int current, FILE*in, int width);
int check_left (int current, FILE*in);
int check_right (int current, FILE*in);
int check_directions(int* array, int direction);
int count_walls(int current, FILE*in, int width);
int count_ways(int current, FILE*in, int width);