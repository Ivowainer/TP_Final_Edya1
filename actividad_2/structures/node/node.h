#ifndef __POINT_TYPE_H__
#define __POINT_TYPE_H__

typedef struct
{
    int i;
    int j;
} Coord;

typedef struct
{
    Coord coord;
    int g;
    int rhs;
    int isObstacle;  // 1: si, 0: no
    int *neighborgs; // ARRIBA, ABAJO, IZQUIERDA y DERECHA
} Node;

void *copy_node(void *);
void print_node(void *);
void delete_node(void *);

#endif