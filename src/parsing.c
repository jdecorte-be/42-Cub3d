#include "../inc/cub3d.h"

int **parse_map(int mapWidth, int mapHeight)
{
    int **map = malloc(sizeof(int *) * mapHeight);
    int i = 0;
    while(i < 10)
    {
        int j = 0;
        map[i] = malloc(sizeof(int) * mapWidth);
        while(j < mapWidth)
        {
            map[i][j] = 0;
            j++;
        }
        i++;
    }
    return map;
}