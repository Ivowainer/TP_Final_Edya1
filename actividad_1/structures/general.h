#ifndef __GENERAL_H__
#define __GENERAL_H__

#include "./bheap/bheap.h"
#include "./node/node.h"
#include "./list/clist.h"

#define INFINITY_U __INT16_MAX__

typedef char **Grid;

typedef Node **Maze;

typedef struct
{
    BHeap *bheap;
    Node *sStart, *sGoal, *sLast;
    int km;
    Maze maze;
    int N, M;
    Grid grid;
} MazeData;

#endif