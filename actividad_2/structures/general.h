#ifndef __GENERAL_H__
#define __GENERAL_H__

#include "./bheap/bheap.h"
#include "./node/node.h"
#include "./list/clist.h"

#define INFINITY_U __INT16_MAX__
#define UNKNOWN_WEIGHT 100

typedef char **Grid;

typedef Node **Maze;

typedef struct
{
    BHeap *bheap;
    Node *sStart, *sGoal, *sLast;
    int km;
    Maze maze;
    int N, M;
} MazeData;

#endif