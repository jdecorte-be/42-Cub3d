#include "../inc/cub3d.h"

void	ft_error(void *arg, int e)
{
	if (e == 2)
		write (2, "malloc\n", 7);
	else if (e == 9)
		write (2, "map error\n", 10);
	exit (1);
}

void	map_init(t_map *map)
{
	map->spawn = 0;
	map->item = 0;
}

void    update_param(t_data *data, double rot)
{
    double oldDirX;
    double oldPlaneX;

    oldDirX = data->pl->dirX;
    data->pl->totalrots += rot;
    data->pl->dirX = data->pl->dirX * cos(rot) - data->pl->dirY * sin(rot);
    data->pl->dirY = oldDirX * sin(rot) + data->pl->dirY * cos(rot);
    oldPlaneX = data->pl->plX;
    data->pl->plX = data->pl->plX * cos(rot) - data->pl->plY * sin(rot);
    data->pl->plY = oldPlaneX * sin(rot) + data->pl->plY * cos(rot);

    if(!ft_strchr("1D",data->map->map[(int)(data->pl->posX + data->pl->dirX * data->pl->deY)][(int)(data->pl->posY)]))
        data->pl->posX += data->pl->dirX * data->pl->deY;
    if(!ft_strchr("1D",data->map->map[(int)(data->pl->posX)][(int)(data->pl->posY + data->pl->dirY * data->pl->deY)]))
        data->pl->posY += data->pl->dirY * data->pl->deY;
    if (!ft_strchr("1D",data->map->map[(int)(data->pl->posX + data->pl->plX * data->pl->deX)][(int)data->pl->posY]))
        data->pl->posX += data->pl->plX * data->pl->deX;
    if (!ft_strchr("1D",data->map->map[(int)data->pl->posX][(int)(data->pl->posY + data->pl->plY * data->pl->deX)]))
        data->pl->posY += data->pl->plY * data->pl->deX;
}

int    launch_game(t_data *data)
{
    void *img = mlx_new_image(data->mlx, screenWidth, screenHeight);
    data->img[0]->p_img = mlx_get_data_addr(img, &data->img[0]->bt,
        &data->img[0]->s_line, &data->img[0]->endian);
    mlx_hook(data->mlx_win, 2, 0, key_handler, data);

    update_param(data, data->pl->rot);
    raycaster(data);
    minimap(data);
    put_hud(data);
    mlx_put_image_to_window(data->mlx, data->mlx_win, img, 0, 0);
    return 0;
}

int free_exit(t_data *data)
{
   mlx_destroy_window(data->mlx, data->mlx_win);
   exit(0);
}

//      data->pl->totalrots += data->pl->rot;
//     data->pl->dirX = data->pl->dirX * cos(data->pl->rot) - data->pl->dirY * sin(data->pl->rot);
//     data->pl->dirY = oldDirX * sin(data->pl->rot) + data->pl->dirY * cos(data->pl->rot);

#define CPL_ROT 2 * M_PI
#define ROTX CPL_ROT / 90

int    mousing(int x, int y, t_data *data)
{
    static int  mx =- 1;
    double      oldDirX;
    int         dx;

    // void *img = mlx_new_image(data->mlx, screenWidth, screenHeight);
    // data->img[0]->p_img = mlx_get_data_addr(img, &data->img[0]->bt,
    //     &data->img[0]->s_line, &data->img[0]->endian);
    // mlx_hook(data->mlx_win, 2, 0, key_handler, data);

    // if (mx == -1)
        // mx = x;
    dx = x - screenWidth / 2;
    if (dx > 0)
    {
        // while (dx--)
            update_param(data, dx * (-ROTX));
    }
    else if (dx < 0)
    {
        // while (dx++)
            update_param(data, -dx * ROTX);
    }
    mlx_mouse_move(data->mlx_win, screenWidth / 2, screenHeight / 2);
    // mx = x;
    return (0);
}

void    set_spawn(t_data *data)
{
    data->map->dirSpawn = ((t_item *)(data->map->spawn->content))->type;
    data->pl->posX = ((t_item *)(data->map->spawn->content))->py + 0.5;
    data->pl->posY = ((t_item *)(data->map->spawn->content))->px + 0.5;
}

int main(int ac, char **av)
{
    if(ac == 1)
        return 0;
    t_data  *data;
    data = malloc(sizeof(t_data));
    if(!data)
        return 0;

    t_map map;
    init_data(data);
    map_init(&map);
	if (parsing(data, &map, av))
        exit (0);
    data->map = &map;
    // find_spawn(data->map->map, data);
    set_spawn(data);
    set_plane(data, data->map->dirSpawn);
    // count_sprites(data);
    // data->map->map = parse_map(data, open(av[1], O_RDONLY));
    // data->map->minimap = data->map->map;

    mlx_mouse_hide();
    mlx_do_key_autorepeaton(data->mlx);
    mlx_hook(data->mlx_win, 2, 0, key_handler, data);
    mlx_hook(data->mlx_win, 3, 0, key_exit, data);
    mlx_hook(data->mlx_win, 6, 0, mousing, data);
    mlx_hook(data->mlx_win, 17, 0, free_exit, data);
	mlx_loop_hook(data->mlx, launch_game, data);
	mlx_loop(data->mlx);
}