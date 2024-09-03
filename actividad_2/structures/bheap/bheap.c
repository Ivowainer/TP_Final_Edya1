#include <stdio.h>
#include "bheap.h"

static void swap_nodes(BHeap *heap, int i, int j)
{
    BHeapNode temp = heap->nodes[i];
    heap->nodes[i] = heap->nodes[j];
    heap->nodes[j] = temp;
}

static void bheap_float(BHeap *heap, int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (compareKeys(heap->nodes[index].key, heap->nodes[parent].key) >= 0)
        {
            break;
        }
        swap_nodes(heap, index, parent);
        index = parent;
    }
}

static void bheap_sink(BHeap *heap, int index)
{
    int size = heap->size;
    while (2 * index + 1 < size)
    {
        int child = 2 * index + 1;
        int right = 2 * index + 2;
        if (right < size && compareKeys(heap->nodes[right].key, heap->nodes[child].key) < 0)
        {
            child = right;
        }
        if (compareKeys(heap->nodes[index].key, heap->nodes[child].key) <= 0)
        {
            break;
        }
        swap_nodes(heap, index, child);
        index = child;
    }
}

BHeap *create_bheap(int capacity)
{
    BHeap *heap = (BHeap *)malloc(sizeof(BHeap));
    heap->nodes = (BHeapNode *)malloc(sizeof(BHeapNode) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void enqueue_bheap(BHeap *heap, Node *node, int *keys)
{
    if (heap->size == heap->capacity)
    {
        heap->capacity *= 2;
        heap->nodes = (BHeapNode *)realloc(heap->nodes, sizeof(BHeapNode) * heap->capacity);
    }

    BHeapNode new_node;
    new_node.node = node;
    new_node.key[0] = keys[0];
    new_node.key[1] = keys[1];

    heap->nodes[heap->size] = new_node;
    bheap_float(heap, heap->size);
    heap->size++;
}

int *topKey_bheap(BHeap *heap)
{
    if (heap->size == 0)
    {
        return NULL;
    }
    return heap->nodes[0].key;
}

Node *dequeue_bheap(BHeap *heap)
{
    if (heap->size == 0)
    {
        return NULL;
    }
    Node *node = heap->nodes[0].node;
    heap->nodes[0] = heap->nodes[--heap->size];
    bheap_sink(heap, 0);
    return node;
}

int search_bheap(BHeap *heap, Node *node)
{
    for (int i = 0; i < heap->size; i++)
    {
        if (heap->nodes[i].node == node)
        {
            return i;
        }
    }
    return -1;
}

void remove_bheap(BHeap *heap, Node *node)
{
    int index = search_bheap(heap, node);
    BHeapNode temp = heap->nodes[index];
    if (index == -1)
    {
        return;
    }
    if (index == heap->size - 1)
    {
        free(temp.key);
        heap->size--;
        return;
    }

    swap_nodes(heap, index, heap->size - 1);
    heap->size--;
    bheap_sink(heap, index);
    bheap_float(heap, index);
    free(temp.key);
}

int compareKeys(int *a, int *b)
{
    if (a[0] != b[0])
    {
        return a[0] - b[0];
    }
    return a[1] - b[1];
}

void destroy_bheap(BHeap *heap)
{
    for (int i = 0; i < heap->size; i++)
        free(heap->nodes[i].key);
    free(heap->nodes);
    free(heap);
}

void print_bheap(BHeap *heap)
{
    for (int i = 0; i < heap->size; i++)
        printf("Coords: (%d, %d), Keys: [%d, %d], ", heap->nodes[i].node->coord.i, heap->nodes[i].node->coord.j, heap->nodes[i].key[0], heap->nodes[i].key[1]);
    printf("\n");
}
