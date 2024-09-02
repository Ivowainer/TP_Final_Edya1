#ifndef __CLIST_H__
#define __CLIST_H__

typedef struct clistNode
{
    struct clistNode *next;
    struct clistNode *prev;
    char *data;
} clistNode;

typedef struct
{
    clistNode *head;
    clistNode *tail;
    int size;
} clist;

clist *clist_create();
void clist_destroy(clist *list);
void clist_push_back(clist *list, char *data);
void clist_print(clist *list);

#endif