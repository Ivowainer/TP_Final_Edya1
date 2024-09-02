#include <stdio.h>
#include <stdlib.h>
#include "clist.h"

clist *clist_create()
{
    clist *list = malloc(sizeof(clist));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void clist_destroy(clist *list)
{
    clistNode *node = list->head;
    while (node != NULL)
    {
        clistNode *next = node->next;
        free(node->data);
        free(node);
        node = next;
    }
    free(list);
}

void clist_push_back(clist *list, char *data)
{
    clistNode *node = malloc(sizeof(clistNode));
    node->data = data;
    node->next = NULL;
    node->prev = list->tail;
    if (list->tail != NULL)
        list->tail->next = node;
    list->tail = node;
    if (list->head == NULL)
        list->head = node;
    list->size++;
}

void clist_print(clist *list)
{
    clistNode *node = list->head;
    while (node != NULL)
    {
        printf("%c", *node->data);
        node = node->next;
    }
}