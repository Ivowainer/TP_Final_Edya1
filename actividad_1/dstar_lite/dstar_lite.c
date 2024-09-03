#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./dstar_lite.h"

static Coord directions_versor(int d)
{
    Coord vd;

    if (d == 0)
    {
        vd.i = -1;
        vd.j = 0;
    }
    else if (d == 1)
    {
        vd.i = 1;
        vd.j = 0;
    }
    else if (d == 2)
    {
        vd.i = 0;
        vd.j = -1;
    }
    else if (d == 3)
    {
        vd.i = 0;
        vd.j = 1;
    }

    return vd;
}

int *calculate_key(Node *node, MazeData *mazeData)
{
    int *key = malloc(sizeof(int) * 2);
    key[0] = fmin(node->g, node->rhs) + h(mazeData->sStart, node) + mazeData->km;
    key[1] = fmin(node->g, node->rhs);

    return key;
}

int getDirection(Node *u, Node *v)
{
    if (u->coord.i - v->coord.i == 1)
        return 0;
    if (u->coord.i - v->coord.i == -1)
        return 1;
    if (u->coord.j - v->coord.j == 1)
        return 2;
    if (u->coord.j - v->coord.j == -1)
        return 3;
    return -1;
}

char *getDirectionChar(Node *u, Node *v)
{
    char *a = malloc(sizeof(char));
    if (u->coord.i - v->coord.i == 1)
        *a = 'U';
    if (u->coord.i - v->coord.i == -1)
        *a = 'D';
    if (u->coord.j - v->coord.j == 1)
        *a = 'L';
    if (u->coord.j - v->coord.j == -1)
        *a = 'R';

    return a;
}

// Siendo k un entero, la función get_coord(u, k) devuelve la coordenada de la casilla vecina de u en la dirección k.
static Coord get_coord(Node *u, int k)
{
    Coord coord;
    coord.i = u->coord.i;
    coord.j = u->coord.j;

    switch (k)
    {
    case 0:
        coord.i = u->coord.i - 1;
        break;
    case 1:
        coord.i = u->coord.i + 1;
        break;
    case 2:
        coord.j = u->coord.j - 1;
        break;
    case 3:
        coord.j = u->coord.j + 1;
        break;
    }

    return coord;
}

static Node *get_neighbor(Node *u, int direction, MazeData *mazeData)
{

    int ni = u->coord.i;
    int nj = u->coord.j;

    switch (direction)
    {
    case 0:
        ni = u->coord.i - 1;
        break;
    case 1:
        ni = u->coord.i + 1;
        break;
    case 2:
        nj = u->coord.j - 1;
        break;
    case 3:
        nj = u->coord.j + 1;
        break;
    default:
        return NULL; // Direccion no valida
    }

    if (ni >= 0 && ni < mazeData->N && nj >= 0 && nj < mazeData->M)
        return &mazeData->maze[ni][nj]; // Devolver la direccion del vecino

    return NULL; // Fuera del del tablero
}

int compCoords(Node *a, Node *b)
{
    if (a->coord.i == b->coord.i && a->coord.j == b->coord.j)
        return 0;
    return 1;
}

int h(Node *a, Node *b)
{
    return abs(a->coord.i - b->coord.i) + abs(a->coord.j - b->coord.j);
}

Node *getMinNeighbor(Node *u, MazeData *mazeData)
{
    Node *min = NULL;
    int min_cost = __INT_MAX__;

    for (int i = 0; i < 4; i++)
    {
        Node *s = get_neighbor(u, i, mazeData);
        int cost = __INT_MAX__;

        if (s != NULL)
            cost = getCost(u, s, mazeData) + s->g;

        if (cost < min_cost)
        {
            min = s;
            min_cost = cost;
        }
    }

    return min;
}

int getCost(Node *u, Node *s, MazeData *mazeData)
{
    int direction = getDirection(u, s);
    return u->neighborgs[direction];
}

void initialize(MazeData *mazeData, Grid grid, int N, int M, int i1, int j1, int i2, int j2)
{
    mazeData->N = N;
    mazeData->M = M;
    mazeData->km = 0;

    Maze maze = malloc(sizeof(Node *) * N);
    for (int i = 0; i < N; i++)
        maze[i] = malloc(sizeof(Node) * M);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            maze[i][j].neighborgs = malloc(sizeof(int) * 4);

            maze[i][j].neighborgs[0] = 2;
            maze[i][j].neighborgs[1] = 2;
            maze[i][j].neighborgs[2] = 2;
            maze[i][j].neighborgs[3] = 2;

            if (j == 0)
                maze[i][j].neighborgs[2] = INFINITY_U;
            else if (j == M - 1)
                maze[i][j].neighborgs[3] = INFINITY_U;
            if (i == 0)
                maze[i][j].neighborgs[0] = INFINITY_U;
            else if (i == N - 1)
                maze[i][j].neighborgs[1] = INFINITY_U;

            maze[i][j].coord.i = i;
            maze[i][j].coord.j = j;
            maze[i][j].g = INFINITY_U;
            maze[i][j].rhs = INFINITY_U;
            maze[i][j].isObstacle = 0;
        }
    }

    mazeData->maze = maze;
    mazeData->bheap = create_bheap(N * M);
    mazeData->sStart = &maze[i1][j1];
    mazeData->sGoal = &maze[i2][j2];
    mazeData->sLast = mazeData->sStart;
    mazeData->grid = grid;

    mazeData->sGoal->rhs = 0;

    enqueue_bheap(mazeData->bheap, mazeData->sGoal, calculate_key(mazeData->sGoal, mazeData));
}

int isObstacle(Node *u, MazeData *mazeData)
{
    if (mazeData->grid[u->coord.i][u->coord.j] == '#')
        return 1;
    return 0;
}

void updateVertex(Node *u, MazeData *mazeData)
{
    if (compCoords(u, mazeData->sGoal))
    {
        Node *s = getMinNeighbor(u, mazeData);

        u->rhs = getCost(u, s, mazeData) + s->g;
    }
    if (search_bheap(mazeData->bheap, u) != -1)
        remove_bheap(mazeData->bheap, u);
    if (u->g != u->rhs)
        enqueue_bheap(mazeData->bheap, u, calculate_key(u, mazeData));
}

void updateWeight(Node *u, MazeData *mazeData)
{
    for (int d = 0; d < 4; d++) // Iteramos en direcciones
    {
        Node *v = get_neighbor(u, d, mazeData);

        if (v != NULL)
        {
            int a = getDirection(v, u);
            if (isObstacle(u, mazeData))
            {
                v->neighborgs[a] = INFINITY_U;
                mazeData->maze[u->coord.i][u->coord.j].isObstacle = 1;
            }
            else
                v->neighborgs[a] = 1;

            updateVertex(v, mazeData);
        }
    }
}

int compare(MazeData *mazeData, int *s)
{
    int *top = topKey_bheap(mazeData->bheap);
    int result = compareKeys(top, s) < 0;

    free(top);
    return result;
}

void computeShortestPath(MazeData *mazeData)
{
    int *s = calculate_key(mazeData->sStart, mazeData);
    while (mazeData->bheap->size > 0 && (compare(mazeData, s) || mazeData->sStart->rhs != mazeData->sStart->g))
    {
        int *k_old = topKey_bheap(mazeData->bheap);
        Node *u = dequeue_bheap(mazeData->bheap);

        int *keys_u = calculate_key(u, mazeData);

        if (compareKeys(k_old, keys_u) < 0)
            enqueue_bheap(mazeData->bheap, u, keys_u);
        else if (u->g > u->rhs)
        {
            u->g = u->rhs;
            for (int i = 0; i < 4; i++)
            {
                Node *s = get_neighbor(u, i, mazeData);

                if (s != NULL)
                    updateVertex(s, mazeData);
            }
            free(keys_u);
        }
        else
        {
            u->g = INFINITY_U;
            for (int i = 0; i < 4; i++)
            {
                Node *s = get_neighbor(u, i, mazeData);

                if (s != NULL)
                    updateVertex(s, mazeData);
            }
            updateVertex(u, mazeData);
            free(keys_u);
        }
        free(k_old);
    }

    free(s);
}