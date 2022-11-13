// ***
// *** You must modify this file
// ***

#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include "fileconv.h"



int main(int argc, char** argv)
{
	// argv[1]: option type
	// argv[2]: name of input file
	// if argc is not 3, return EXIT_FAILURE
	if (argc < 3) {
		return EXIT_FAILURE;
	}
	char * filename= argv[2];
	char *option=argv[1];
	if(!(strcmp(option,"-b")==0||strcmp(option,"-e")==0)){
		return EXIT_FAILURE;
	}

	if(strcmp(option,"-b")==0){
		FILE* fptr = fopen(filename, "rb");
		if (fptr == NULL) {
			printf("-1");
			return EXIT_FAILURE;
		}
		 int *key;
		int *ops;
		readOpsFromFile(filename,&key,&ops);

	}
	if(strcmp(option,"-e")==0){
		
	}
	return EXIT_SUCCESS;


}
int readOpsFromFile(char *fileName,int  **key,int **opr)
{

    FILE *fptr;
    int size = 0;
    fptr = fopen(fileName, "rb");
    if (fptr == NULL)
    {
        return size;
    }

    fseek(fptr, 0L, SEEK_END);
    int fileSize = ftell(fptr);
    size = fileSize / (sizeof(int) + sizeof(char));
    if (fileSize != size * (sizeof(int) + sizeof(char)))
    {
        printf("invalid file size");
        return 0;
    }

    int *arr = malloc(sizeof(int) * size);
    int *oprArr = malloc(sizeof(char) * size);
	*key=arr;
	*opr=oprArr;
    fseek(fptr, 0, SEEK_SET);
    int ind = 0;
    while (ind < size)
    {
        while (fread(&arr[ind], sizeof(int), 1, fptr))
        {
            fread(&oprArr[ind], sizeof(char), 1, fptr);
            ind++;
        }
    }
    fclose(fptr);
    return size;
    
}


