#include "../inc/cub3d.h"

void    update_param(t_data *data)
{
    double oldDirX;
    double oldPlaneX;

    oldDirX = data->pl->dirX;
    data->pl->dirX = data->pl->dirX * cos(data->pl->rot) - data->pl->dirY * sin(data->pl->rot);
    data->pl->dirY = oldDirX * sin(data->pl->rot) + data->pl->dirY * cos(data->pl->rot);
    oldPlaneX = data->pl->plX;
    data->pl->plX = data->pl->plX * cos(data->pl->rot) - data->pl->plY * sin(data->pl->rot);
    data->pl->plY = oldPlaneX * sin(data->pl->rot) + data->pl->plY * cos(data->pl->rot);

    if(data->map->map[(int)(data->pl->posX + data->pl->dirX * data->pl->deY)][(int)(data->pl->posY)] != '1')
        data->pl->posX += data->pl->dirX * data->pl->deY;
    if(data->map->map[(int)(data->pl->posX)][(int)(data->pl->posY + data->pl->dirY * data->pl->deY)] != '1')
        data->pl->posY += data->pl->dirY * data->pl->deY;

    if (data->map->map[(int)(data->pl->posX + data->pl->plX * data->pl->deX)][(int)data->pl->posY] != '1')
        data->pl->posX += data->pl->plX * data->pl->deX;
    if (data->map->map[(int)data->pl->posX][(int)(data->pl->posY + data->pl->plY * data->pl->deX)] != '1')
        data->pl->posY += data->pl->plY * data->pl->deX;
}

int    launch_game(t_data *data)
{
    void *img = mlx_new_image(data->mlx, screenWidth, screenHeight);
    data->img[0]->p_img = mlx_get_data_addr(img, &data->img[0]->bt,
        &data->img[0]->s_line, &data->img[0]->endian);
    mlx_hook(data->mlx_win, 2, 0, key_handler, data);

    update_param(data);
    raycaster(data);
    // minimap(data);

    mlx_put_image_to_window(data->mlx, data->mlx_win, img, 0, 0);
    return 0;
}

int main(int ac, char **av)
{
    if(ac == 1)
        return 0;
    t_data  *data;
    data = malloc(sizeof(t_data));
    if(!data)
        return 0;

    init_data(data);

    data->map->map = parse_map(data, open(av[1], O_RDONLY));

    mlx_do_key_autorepeaton(data->mlx);
    mlx_hook(data->mlx_win, 2, 0, key_handler, data);
    mlx_hook(data->mlx_win, 3, 0, key_exit, data);
    
	mlx_loop_hook(data->mlx, launch_game, data);
	mlx_loop(data->mlx);
}