#ifndef __GRID_NODE__
#define __GRID_NODE__

typedef struct _xy
{
   short x;
   short y;
} XY;

typedef struct _gnode
{
   XY parent;
   short waitTime;
   short mintime;
} GNode;
typedef struct _pnode
{
   XY node;
   struct _pnode *next;
} PNode;
#endif
