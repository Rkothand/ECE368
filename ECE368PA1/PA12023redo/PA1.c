
#include "shell_array.h"
#include "shell_array.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

// long *createLongArry()
// {
//     long *arr = malloc(sizeof(long) * 10);
//     int i = 0;
//     for (i = 0; i < 10; i++)
//     {
//         arr[i] = (long)i;
//     }
//     return arr;
// }

int main(int argc, char **argv)
{
    int count = 0;
    long *a = Array_Load_From_File("input/1K.b", &count);
    long cc;
    Array_Shellsort(a, count, &cc);
    printf(" wrote %d to file %s", count, "output/out1");
    return 0;
    
/*
    long *a = createLongArry();

    int w = Array_Save_To_File((char*)"./output/o1.txx", a, 10);
    int count=0;
    long cc;
    a=Array_Load_From_File("input/1K.b", &count);
    Array_Shellsort(a,count,&cc);
    // printf(" wrote %d to file %s", w, "output/out1");
    return 0;
*/
}