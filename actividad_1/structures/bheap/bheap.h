#ifndef __BHEAP_H__
#define __BHEAP_H__

#include <stdio.h>
#include <stdlib.h>

#include "../structures/node/node.h"

typedef struct
{
    Node *node;
    int *key;
} BHeapNode;

typedef struct
{
    BHeapNode *nodes;
    int size;
    int capacity;
} BHeap;

BHeap *create_bheap(int capacity);
void enqueue_bheap(BHeap *heap, Node *node, int *keys);

void remove_bheap(BHeap *heap, Node *node);

int *topKey_bheap(BHeap *heap);
Node *dequeue_bheap(BHeap *heap);

int search_bheap(BHeap *heap, Node *node);

int compareKeys(int *a, int *b);
void print_bheap(BHeap *heap);

void destroy_bheap(BHeap *heap);

#endif