#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "fileconv.h"

int checkFileStatus(char *fileName, char *mode)
{
    FILE *fptr = fopen(fileName, mode);
    if (fptr == NULL)
    {

        return EXIT_FAILURE;
    }
    fclose(fptr);
    return 0;
}

GNode **readGridFile(char *fileName, short *m, short *n)
{

    FILE *fptr = fopen(fileName, "rb");
    fread(m, sizeof(short), 1, fptr);
    fread(n, sizeof(short), 1, fptr);
    short lm = *m;
    short ln = *n;
    //Allocate array memory- one row extra to hold final result
    GNode **grid = malloc(sizeof(GNode *) * (lm + 1));
    if (grid == NULL)
    {
        //graceful exit
        return grid;
    }
    short r, c;
    for (r = 0; r < lm + 1; r++)
    {
        grid[r] = (GNode *)malloc(sizeof(GNode) * ln);
        if (grid[r] == NULL)
        {
            //Graceful exit
            return grid;
        }
    }
    //read from the file
    for (r = 0; r < lm; r++)
    {
        for (c = 0; c < ln; c++)
        {
            fread(&grid[r][c].waitTime, sizeof(short), 1, fptr);
        }
    }

    fclose(fptr);

    return grid;
}

int writeToFile(char *fileName, GNode **grid, short m, short n)
{

    FILE *fptr = fopen(fileName, "w");
    fprintf(fptr, "%hd %hd\n", m, n);

    short r, c;

    for (r = 0; r < m; r++)
    {
        for (c = 0; c < n; c++)
        {
            char *fmt = "%hd ";
            if (c + 1 == n)
                fmt = "%hd\n";
            fprintf(fptr, fmt, grid[r][c].waitTime);
        }
    }

    fclose(fptr);
    return 0;
}
void printGrid(GNode **grid, short m, short n)
{
    int r, c;
    printf("\n ");
    for (r = 0; r < m; r++)
    {

        for (c = 0; c < n; c++)
        {
            printf("%d ", grid[r][c].waitTime);
        }
        printf("\n ");
    }
}
void printGridMintime(GNode **grid, short m, short n)
{
    int r, c;
    printf("\n ");
    for (r = 0; r < m; r++)
    {

        for (c = 0; c < n; c++)
        {
            printf("%d ", grid[r][c].mintime);
        }
        printf("\n ");
    }
}

void fillLast(GNode **gnode, short m, short n, short cx, short cy)
{
    //from top

    if (cx > 0 && (gnode[cx - 1][cy].waitTime + gnode[cx - 1][cy].mintime < gnode[cx][cy].mintime))
    {
        gnode[cx][cy].mintime = gnode[cx - 1][cy].waitTime + gnode[cx - 1][cy].mintime;
        gnode[cx][cy].parent.x = cx - 1;
        gnode[cx][cy].parent.y = cy;
    }
}
bool fillMin(GNode **gnode, short m, short n, short *cxp, short *cyp)
{
    bool changed = false;
    short cx = *cxp;
    short cy = *cyp;
    //from left
    if (cy > 0 && (gnode[cx][cy - 1].waitTime + gnode[cx][cy - 1].mintime < gnode[cx][cy].mintime))
    {
        gnode[cx][cy].mintime = gnode[cx][cy - 1].waitTime + gnode[cx][cy - 1].mintime;
        gnode[cx][cy].parent.x = cx;
        gnode[cx][cy].parent.y = cy - 1;
        changed = true;
    }

    if (cy > 0 && (gnode[cx][cy].waitTime + gnode[cx][cy].mintime < gnode[cx][cy - 1].mintime))
    {
        gnode[cx][cy - 1].mintime = gnode[cx][cy].waitTime + gnode[cx][cy].mintime;
        gnode[cx][cy - 1].parent.x = cx;
        gnode[cx][cy - 1].parent.y = cy;
        *cyp = cy - 1;
        changed = true;
    }
    //from top

    if (cx > 0 && (gnode[cx - 1][cy].waitTime + gnode[cx - 1][cy].mintime < gnode[cx][cy].mintime))
    {
        gnode[cx][cy].mintime = gnode[cx - 1][cy].waitTime + gnode[cx - 1][cy].mintime;
        gnode[cx][cy].parent.x = cx - 1;
        gnode[cx][cy].parent.y = cy;
        changed = true;
    }
    //right

    if (cy + 1 < n && (gnode[cx][cy + 1].waitTime + gnode[cx][cy + 1].mintime < gnode[cx][cy].mintime))
    {
        gnode[cx][cy].mintime = gnode[cx][cy + 1].waitTime + gnode[cx][cy + 1].mintime;
        gnode[cx][cy].parent.x = cx;
        gnode[cx][cy].parent.y = cy + 1;
        changed = true;
    }
    return changed;
}
void printPath(PNode *head)
{
    while (head->next != NULL)
    {
        printf("x=%hd,y=%hd\n", head->node.x, head->node.y);
        head = head->next;
    }
}

void writeFastTimesPerColumn(char *fileName, int *fastTime, short size)
{
    FILE *fptr = fopen(fileName, "wb");
    if (fptr == NULL)
    {
        return;
    }
    fwrite(&size, sizeof(short), 1, fptr);
    fwrite(fastTime, sizeof(int), size, fptr);
    fclose(fptr);
}

void writeGridPath(char *fileName, PNode *head, short size, int minFast)
{
    FILE *fptr = fopen(fileName, "wb");
    if (fptr == NULL)
    {
        return;
    }
    int f = (int)minFast;
    int s = (int)size;
    fwrite(&f, sizeof(int), 1, fptr);
    fwrite(&s, sizeof(int), 1, fptr);

    while (head != NULL)
    {
        fwrite(&head->node.x, sizeof(short), 1, fptr);
        fwrite(&head->node.y, sizeof(short), 1, fptr);
        head = head->next;
    }
    fclose(fptr);
}

void writeGridTextPath(char *fileName, PNode *head, short size, int minFast)
{

    char name[50];
    strcpy(name, fileName);
    FILE *fptr = fopen(strcat(name, "t"), "w");
    if (fptr == NULL)
    {
        return;
    }

    fprintf(fptr, "%d\n", (int)minFast);
    fprintf(fptr, "%d\n", (int)size);
    while (head != NULL)
    {
        fprintf(fptr, "%hd %hd\n", head->node.x, head->node.y);
        head = head->next;
    }
    fclose(fptr);
}

void writeTextFastTimesPerColumn(char *fileName, int *fastTimes, short n)
{
    char name[50];
    strcpy(name, fileName);
    FILE *fptr = fopen(strcat(name, "t"), "w");
    fprintf(fptr, "%hd\n", n);
    short c;
    for (c = 0; c < n; c++)
    {
        char *fmt = "%d ";
        if (c + 1 == n)
        {
            fmt = "%d\n";
        }
        fprintf(fptr, fmt, fastTimes[c]);
    }
    fclose(fptr);
}
PNode *findFastPath(GNode **grid, short m, short n, short minC, short *pathSize, int *ptrPathTime)
{
    short px, py;
    int pathTime = 0;
    PNode *head = NULL;
    //pathTime+=grid[m][minC].waitTime;
    px = m - 1;
    py = minC;
    //first node
    PNode *cnode = (PNode *)malloc(sizeof(PNode));
    cnode->next = NULL;
    cnode->node.x = px;
    cnode->node.y = py;
    head = cnode;

    short size = 1;

    while (true)
    {
        //printf("x= %hd, y= %hd \n", px, py);
        if (grid[px][py].parent.x == -1 && grid[px][py].parent.y == -1)
            break;
        int tpx = grid[px][py].parent.x;
        int tpy = grid[px][py].parent.y;
        pathTime = pathTime + grid[px][py].waitTime;
        px = tpx;
        py = tpy;
        cnode = (PNode *)malloc(sizeof(PNode));
        cnode->next = head;
        cnode->node.x = px;
        cnode->node.y = py;
        //New head
        head = cnode;
        size++;
    }
    pathTime += grid[px][py].waitTime;
    *pathSize = size;
    *ptrPathTime = pathTime;

    return head;
}
void findAllMinPath(GNode **grid, short m, short n, short startCol)
{
    //Initialize
    short r, c;
    for (r = 0; r < m + 1; r++)
    {
        for (c = 0; c < n; c++)
        {
            grid[r][c].mintime = __SHRT_MAX__;
            grid[r][c].parent.x = -1;
            grid[r][c].parent.x = -1;
        }
    }
    //start of the grid
    grid[0][startCol].mintime = 0;
    grid[0][startCol].parent.x = -1;
    grid[0][startCol].parent.y = -1;
    for (r = 0; r < m; r++)
    {
        c = startCol;
        while (c >= 0)
        {
            while (fillMin(grid, m, n, &r, &c))
                ;
            c--;
        }
        c = startCol;
        while (c < n)
        {
            while (fillMin(grid, m, n, &r, &c))
                ;
            c++;
        }

        c = 0;
        while (c < n)
        {
            while (fillMin(grid, m, n, &r, &c))
                ;
            c++;
        }
    }
    //fill the last row
    c = 0;
    r = m;
    while (c < n)
    {
        fillLast(grid, m, n, r, c);
        c++;
    }
}
void deleteLinkList(PNode *head)
{
    while (head != NULL)
    {
        PNode *n = head->next;
        free(head);
        head = n;
    }
}
void freeGrid(GNode **g, short m, short n)
{
    int i;
    //free m+1 records-as last row holds final result
    for (i = 0; i < m + 1; i++)
    {
        free(g[i]);
    }
    free(g);
}