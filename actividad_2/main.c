#include "./structures/general.h"
#include "./structures/node/node.h"
#include "./structures/bheap/bheap.h"
#include "./structures/list/clist.h"

#include "./temp/sensor_temp.h"
#include "./dstar_lite/dstar_lite.h"

#include <stdio.h>
#include <stdlib.h>

int *sensor(Coord a)
{
    int *distances = malloc(sizeof(int) * 4);
    printf("? %d %d\n", a.i, a.j);
    fflush(stdout);
    scanf("%d%d%d%d", distances, distances + 1, distances + 2, distances + 3);
    return distances;
}

int main()
{
    int N, M, D;
    int i1, j1;
    int i2, j2;

    scanf("%d %d %d", &N, &M, &D);
    scanf("%d %d", &i1, &j1);
    scanf("%d %d", &i2, &j2);

    clist *list = clist_create();

    MazeData *maze_data = malloc(sizeof(MazeData));
    maze_data->sLast = maze_data->sStart;
    initialize(maze_data, N, M, i1, j1, i2, j2);
    computeShortestPath(maze_data);
    Node *sGoal = maze_data->sGoal;

    int i = 0;

    while (compCoords(maze_data->sStart, sGoal))
    {
        if (i == 100)
        {
            printf("! RRUU\n");
            fflush(stdout);
            return -1;
        }
        Node *min = getMinNeighbor(maze_data->sStart, maze_data);

        if (getCost(maze_data->sStart, min, maze_data) > 1)
        {
            maze_data->km += h(maze_data->sLast, maze_data->sStart);
            maze_data->sLast = maze_data->sStart;

            int *distances = sensor(maze_data->sStart->coord);

            updateWeights(maze_data->sStart, distances, maze_data, D);

            computeShortestPath(maze_data);
        }
        else
        {
            clist_push_back(list, getDirectionChar(maze_data->sStart, min));
            maze_data->sStart = min;
        }
    }

    printf("! ");
    clist_print(list);
    printf("\n");
    fflush(stdout);

    return 0;
}