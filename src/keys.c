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

void    set_dir(t_data *ptr, char flag)
{
	if (flag == 'W')
	{
        ptr->pl->dirX = 1;
		ptr->pl->dirY = -1;
	}
	else if (flag == 'E')
	{
        ptr->pl->dirX = 1;
		ptr->pl->dirY = 1;
	}
	else if (flag == 'N')
	{
        ptr->pl->dirY = 1;
		ptr->pl->dirX = -1;
	}
	else if (flag == 'S')
	{
        ptr->pl->dirY = 1;
		ptr->pl->dirX = 1;
	}
}

int    key_handler(int key, t_data *data)
{
    printf("%d\n", key);
    if(key == 53)
    {
         mlx_destroy_window(data->mlx, data->mlx_win);
        exit(0);
    }
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
    if (key == 126)
    {
        pl_init(data);
        data->map->spawn = data->map->spawn->next;
        set_spawn(data);
        set_plane(data, data->map->dirSpawn);
    }
    if (key == 125)
    {
        pl_init(data);
        data->map->spawn = data->map->spawn->prev;
        set_spawn(data);
        set_plane(data, data->map->dirSpawn);
    }
    return 0;
}

