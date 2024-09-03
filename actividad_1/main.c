#include "./structures/general.h"
#include "./structures/node/node.h"
#include "./structures/bheap/bheap.h"
#include "./structures/list/clist.h"

#include "./dstar_lite/dstar_lite.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Grid read_file(int *N, int *M, int *D, int *i1, int *j1, int *i2, int *j2, char *file_name);
void free_all(MazeData *mazeData, Grid grid, clist *list);

void print_maze(MazeData *mazeData)
{
    for (int i = 0; i < mazeData->N; i++)
    {
        if (i < 10)
            printf("%d.  ", i);
        else
            printf("%d. ", i);

        for (int j = 0; j < mazeData->M; j++)
        {

            if (mazeData->sStart->coord.i == i && mazeData->sStart->coord.j == j)
                printf("S");
            else if (mazeData->sGoal->coord.i == i && mazeData->sGoal->coord.j == j)
                printf("G");
            else if (mazeData->maze[i][j].isObstacle)
                printf("#");

            else
                printf(".");
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Por favor, introduce el nombre del archivo \n");
        return -1;
    }

    int N, M, D;
    int i1, j1;
    int i2, j2;

    Grid grid = read_file(&N, &M, &D, &i1, &j1, &i2, &j2, argv[1]);

    if (grid == NULL)
    {
        printf("Error: No se pudo leer el archivo\n");
        return -1;
    }

    clist *list = clist_create();

    MazeData *maze_data = malloc(sizeof(MazeData));
    maze_data->sLast = maze_data->sStart;
    initialize(maze_data, grid, N, M, i1, j1, i2, j2);
    computeShortestPath(maze_data);

    while (compCoords(maze_data->sStart, maze_data->sGoal))
    {
        Node *min = getMinNeighbor(maze_data->sStart, maze_data);

        updateWeight(min, maze_data);

        if (getCost(maze_data->sStart, min, maze_data) > 1)
        {
            maze_data->km += h(maze_data->sLast, maze_data->sStart);
            maze_data->sLast = maze_data->sStart;

            computeShortestPath(maze_data);
        }
        else
        {
            clist_push_back(list, getDirectionChar(maze_data->sStart, min));
            maze_data->sStart = min;
        }
    }

    clist_print(list);
    free_all(maze_data, grid, list);

    return 0;
}

void free_all(MazeData *mazeData, Grid grid, clist *list)
{
    for (int i = 0; i < mazeData->N; i++)
    {
        for (int j = 0; j < mazeData->M; j++)
            free(mazeData->maze[i][j].neighbors);
        free(mazeData->maze[i]);
        free(grid[i]);
    }
    destroy_bheap(mazeData->bheap);
    clist_destroy(list);
    free(mazeData->maze);
    free(grid);
    free(mazeData);
}

Grid read_file(int *N, int *M, int *D, int *i1, int *j1, int *i2, int *j2, char *file_name)
{
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        printf("Error: No existe el archivo indicado");
        return NULL;
    }

    if (fscanf(file, "%d%d%d", N, M, D) != 3)
    {
        fclose(file);
        return NULL;
    }

    if (fscanf(file, "%d %d", i1, j1) != 2)
    {
        fclose(file);
        return NULL;
    }

    if (fscanf(file, "%d %d", i2, j2) != 2)
    {
        fclose(file);
        return NULL;
    }

    if (*i1 < 0 || *i1 >= *N || *j1 < 0 || *j1 >= *M || *i2 < 0 || *i2 >= *N || *j2 < 0 || *j2 >= *M)
    {
        printf("Error: las posiciones inicial (%d, %d) o final (%d, %d) estan fuera dell laberinto\n", *i1, *j1, *i2, *j2);
        fclose(file);
        return NULL;
    }

    fscanf(file, "%d %d %d", N, M, D);
    fscanf(file, "%d %d", i1, j1);
    fscanf(file, "%d %d", i2, j2);

    Grid grid = malloc(sizeof(char *) * (*N));

    for (int i = 0; i < *N; i++)
    {
        grid[i] = malloc(sizeof(char) * ((*M) + 1));
        /* fscanf(file, "%s", grid[i]); */
        if (fscanf(file, "%s", grid[i]) == EOF || strlen(grid[i]) != *M)
        {
            fclose(file);
            printf("Error al leer fila del laberinto\n");
            return NULL;
        }
    }

    fclose(file);

    return grid; // [[... M], ["....#...##."], [".#..#.#..##"], ..., N]
}
