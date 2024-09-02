#ifndef __DSTAR_LITE_H__
#define __DSTAR_LITE_H__

#include "../structures/bheap/bheap.h"
#include "../structures/node/node.h"

#include "../structures/general.h"

void initialize(MazeData *mazeData, Grid grid, int N, int M, int i1, int j1, int i2, int j2);
void computeShortestPath(MazeData *mazeData);

int compCoords(Node *a, Node *b);

Node *getMinNeighbor(Node *u, MazeData *mazeData);
int getCost(Node *u, Node *s, MazeData *mazeData);
int h(Node *a, Node *b);

void updateWeight(Node *u, MazeData *mazeData);
int getDirection(Node *u, Node *v);
char *getDirectionChar(Node *u, Node *v);

#endif