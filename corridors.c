#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>


char wsum(char*ways){
    char sum=0;
    for (int i=0;i<4;i++){
        if (ways[i] == 'X')
            sum++;
    }
    return sum;
}


bool check_if_corridor (char* ways){
    char sum = wsum(ways);



    if (sum == 2){
        if(ways[0] == 'X' && ways[2] == 'X') 
            return true;
        if (ways[1] == 'X' && ways[3] == 'X') 
            return true;
    }
    return false; 
}
