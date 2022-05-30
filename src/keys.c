#include "../inc/cub3d.h"

int    key_exit(int key, t_data *data)
{
    if(key == 123)
        data->pl->rot = 0;
    if(key == 124)
        data->pl->rot = 0;
    if(key == 123)
        data->pl->rot = 0;
    if(key == 124)
        data->pl->rot = 0;
    if(key == 13) // up
        data->pl->deY = 0;
    if(key == 1) // down
        data->pl->deY = 0;
    if(key == 2) // left
        data->pl->deX = 0;
    if(key == 0) // right
        data->pl->deX = 0;
    return 0;
}


int    key_handler(int key, t_data *data)
{
    printf("%d\n", key);
    if(key == 14)
    {
        if(data->map->map[(int)(data->pl->posX - 1.0)][(int)(data->pl->posY)] == 'D')
            data->map->map[(int)(data->pl->posX - 1.0 + data->pl->dirX * data->pl->deY)][(int)(data->pl->posY)] = '0';
        else if (data->map->map[(int)(data->pl->posX + 1.0)][(int)(data->pl->posY)] == 'D')
            data->map->map[(int)(data->pl->posX + 1.0 + data->pl->dirX * data->pl->deY)][(int)(data->pl->posY)] = '0';
        else if (data->map->map[(int)(data->pl->posX)][(int)(data->pl->posY + 1.0)] == 'D')
            data->map->map[(int)(data->pl->posX + data->pl->dirX * data->pl->deY)][(int)(data->pl->posY + 1.0)] = '0';
        else if (data->map->map[(int)(data->pl->posX)][(int)(data->pl->posY - 1.0)] == 'D')
            data->map->map[(int)(data->pl->posX + data->pl->dirX * data->pl->deY)][(int)(data->pl->posY - 1.0)] = '0';
    }
    if(key == 13) // up
        data->pl->deY = 0.1;
    if(key == 1) // down
        data->pl->deY = -0.1;
    if(key == 2) // left
        data->pl->deX = 0.1;
    if(key == 0) // right
        data->pl->deX = -0.1;
    if(key == 123)
        data->pl->rot = 0.1;
    if(key == 124)
        data->pl->rot = -0.1;
    return 0;
}

