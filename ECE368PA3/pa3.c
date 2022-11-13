
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fwt.h"
#include "fileconv.h"

int main(int argc, char **argv)
{
    // argv[1]: input bin file
    // argv[2]: text output file
    // argv[3]: fast times file
    // argv[4]: fastest path file

    if (argc < 4)
    {
        return EXIT_FAILURE;
    }

    char *inputBinFile = argv[1];

    char *writeTextFile = argv[2];
    char *fastTimesFile = argv[3];
    char *fastestPathFile = argv[4];

    if (checkFileStatus(inputBinFile, "rb") != 0)
    {
        return EXIT_FAILURE;
    }
    short m, n;
    GNode **grid = readGridFile(inputBinFile, &m, &n);
    if (grid == NULL)
    {
        return EXIT_FAILURE;
    }
    writeToFile(writeTextFile, grid, m, n);

    int c = 0;
    int ic = 0;
    short min;
    int *fastTimes = malloc(sizeof(int) * n);
    int minFast = __INT_MAX__;
    PNode *minFastPath = NULL;
    short minFastPathSize = 0;

    for (c = 0; c < n; c++)
    {
        findAllMinPath(grid, m, n, c);
        min = grid[m][c].mintime;
        short minC = c;
        for (ic = 0; ic < n; ic++)
        {
            if (grid[m][ic].mintime < min)
            {
                min = grid[m][ic].mintime;
                minC = ic;
            }
        }

        fastTimes[c] = min;

        if (min < minFast)
        {
            minFast = min;
            if (minFastPath != NULL)
            {
                deleteLinkList(minFastPath);
            }
            short pathSize = 0;
            int pathTime = 0;
            PNode *path = findFastPath(grid, m, n, minC, &pathSize, &pathTime);
            minFastPath = path;
            minFastPathSize = pathSize;
        }
    }

    
    writeFastTimesPerColumn(fastTimesFile, fastTimes, n);
    writeGridPath(fastestPathFile, minFastPath, minFastPathSize, (int)minFast);
    //Write text versions
    writeTextFastTimesPerColumn(fastTimesFile, fastTimes, n);
    writeGridTextPath(fastestPathFile, minFastPath, minFastPathSize, (int)minFast);
    //Delete grid, minFastpath and fastTimes.
    freeGrid(grid, m, n);
    free(fastTimes);
    deleteLinkList(minFastPath);
    return EXIT_SUCCESS;
}
