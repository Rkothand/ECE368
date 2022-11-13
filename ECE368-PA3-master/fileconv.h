#include "fwt.h"
int checkFileStatus(char *fileName, char *mode);
void findAllMinPath(GNode **grid, short m, short n, short startCol);
GNode **readGridFile(char *fileName, short *m, short *n);
void printGrid(GNode **grid, short m, short n);
int writeToFile(char *fileName, GNode **grid, short m, short n);
void printGridMintime(GNode **grid, short m, short n);
void findAllMinPath(GNode **grid, short m, short n, short startCol);
PNode *findFastPath(GNode **grid, short m, short n, short minC, short *pathSize,int *minTime);
void printPath(PNode *head);
void writeGridPath(char *fileName,PNode *head,short size,int min);
void writeGridTextPath(char *fileName,PNode *head,short size,int minFast);
void writeFastTimesPerColumn(char *fileName, int *fastTime, short size);
void writeTextFastTimesPerColumn(char *fileName, int *fastTime, short size);
void deleteLinkList(PNode *head);
void freeGrid(GNode **g, short m, short n);