#include "node.h"

#include <stdio.h>
#include <stdlib.h>

void *copy_node(void *node)
{
    Node *p = malloc(sizeof(Node));
    p->coord.i = ((Node *)node)->coord.i;
    p->coord.j = ((Node *)node)->coord.j;
    return p;
}

void print_node(void *node)
{
    Node *p = (Node *)node;
    printf("(%d, %d) g: %d, rhs: %d\n", p->coord.i, p->coord.j, p->g, p->rhs);
}

void delete_node(void *node) { free(node); }