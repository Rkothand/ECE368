#include "shell_list.h"
#include "shell_array.h"
#include "list_of_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

long Array_Load_From_File(char* filename, int *size){
    FILE *fptr;
    fptr = fopen(filename, "rb");
    if (fptr == NULL)
    {
        *size = 0;
        return NULL;
    }
    else
    {
        int numLong = 0;
        long value;
        while (fread(&value, sizeof(long), 1, fptr))        
        {
            numLong++;
        }
        if (numLong == 0)
        {
            *size = 0;
            return NULL;
        }

        *size = numLong;
        long *arr = malloc(sizeof(long) * numLong);
        fseek(fptr, 0, SEEK_SET);
        int ind = 0;
        while (ind < numLong)
        {
            while (fread(&arr[ind], sizeof(long), 1, fptr))
            {
            ind++;    
            }
            
        }
        fclose(fptr);
        return arr;
    }
}


void Array_Shellsort(long *array, int size, long *n comp){
    int i, j, k, increment;
    long temp;
    *ncomp = 0;
    for (increment = size / 2; increment > 0; increment /= 2)
    {
        for (i = increment; i < size; i++)
        {
            for (j = i - increment; j >= 0; j -= increment)
            {
                (*ncomp)++;
                if (array[j + increment] >= array[j])
                    break;
                else
                {
                    temp = array[j];
                    array[j] = array[j + increment];
                    array[j + increment] = temp;
                }
            }
        }
    }
}

/*
long *Array_Load_From_File(char *filename, int *size)
{

    FILE *fptr;
    fptr = fopen(filename, "rb");
    if (fptr == NULL)
    {
        *size = 0;
        return NULL;
    }
    else
    {
        int numLong = 0;
        long value;
        while (fread(&value, sizeof(long), 1, fptr))        
        {
            numLong++;
        }
        if (numLong == 0)
        {
            *size = 0;
            return NULL;
        }

        *size = numLong;
        long *arr = malloc(sizeof(long) * numLong);
        fseek(fptr, 0, SEEK_SET);
        int ind = 0;
        while (ind < numLong)
        {
            while (fread(&arr[ind], sizeof(long), 1, fptr))
            {
            ind++;    
            }
            
        }
        fclose(fptr);
        return arr;
    }
}

int Array_Save_To_File(char *filename, long *array, int size)
{

    FILE *fptr = fopen(filename, "wb");
    int saveCount = 0;
    if (fptr == NULL || size == 0 || array == NULL)
    {
        fclose(fptr);
        return 0;
    }
    else
    {
        saveCount = fwrite(array, sizeof(long), size, fptr);
    }
    fclose(fptr);
    return saveCount;
}

int knuthFunc(int p)
{
    if (p < 1)
        return 0;

    if (p == 1)
        return 1;
    return 3 * kunthFunc(p - 1) + 1;
}

void Array_Shellsort(long *array, int size, long *n_comp){
     int b=0;
     int p;
     int gap[size];
    for(p=1;p<size;p++){
        int v=kunthFunc(p);
        if(v>size){           

            break;
        }
        gap[p-1] =v;
    }
   // printf("value %d",gap);
    int index = 0;
    int k =0;
    int j =0;
    int i =0;

    for(index = p-1; index>=0; index--){
        k = gap[index];
        for(j=k; j<p-1; j++){
            int tempr = array[j];
            int i=j;
                while(i>= k&& array[i-k] >tempr){
                array[i] = array[i-k];
                i = i-k;
                *n_comp= *n_comp+1;
            }
            array[i] = tempr;
        }
    }

/*
    int outer=0;
    int inner=0;
for(outer=0;outer<gap;outer++){

        for(inner=gap;inner<size;inner++){
            if(cmp(array[outer],array[outer+inner])
        }
    
*/
}
*/