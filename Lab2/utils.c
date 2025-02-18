#include "utils.h"

int read_int(){
    int res, val;
    do{
        res = scanf("%d", &val);
    }while(res != 1);
    return val;
}

int read_int_min(int min){
    int res, val;
    do{
        res = scanf("%d", &val);
        if (val < min) {
            printf("Minimum value: %d\n", min);
        }
    }while((res != 1)||(val < min));
    return val;
}

void read_filename(char* filename){
    int res;
    do{
        res = scanf("%s", filename);
    }while(res != 1);
}

int max(int a, int b){
    return (a>b?a:b);
}