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

void    update_param(t_data *data)
{
    double oldDirX;
    double oldPlaneX;

    oldDirX = data->pl->dirX;
    data->pl->totalrots += data->pl->rot;
    data->pl->dirX = data->pl->dirX * cos(data->pl->rot) - data->pl->dirY * sin(data->pl->rot);
    data->pl->dirY = oldDirX * sin(data->pl->rot) + data->pl->dirY * cos(data->pl->rot);
    oldPlaneX = data->pl->plX;
    data->pl->plX = data->pl->plX * cos(data->pl->rot) - data->pl->plY * sin(data->pl->rot);
    data->pl->plY = oldPlaneX * sin(data->pl->rot) + data->pl->plY * cos(data->pl->rot);

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
    printf("--->%d %d \n", ((t_item *)data->map->item->content)->px, ((t_item *)data->map->item->content)->py);
    exit(0);
    void *img = mlx_new_image(data->mlx, screenWidth, screenHeight);
    data->img[0]->p_img = mlx_get_data_addr(img, &data->img[0]->bt,
        &data->img[0]->s_line, &data->img[0]->endian);
    mlx_hook(data->mlx_win, 2, 0, key_handler, data);

    update_param(data);
    raycaster(data);
    minimap(data);
    mlx_put_image_to_window(data->mlx, data->mlx_win, img, 0, 0);
    put_hud(data);
    return 0;
}

int free_exit(t_data *data)
{
   mlx_destroy_window(data->mlx, data->mlx_win);
   exit(0);
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
    find_spawn(data->map->map, data);
    set_plane(data, data->map->dirSpawn);
    // count_sprites(data);
    // data->map->map = parse_map(data, open(av[1], O_RDONLY));
    // data->map->minimap = data->map->map;

    mlx_do_key_autorepeaton(data->mlx);
    mlx_hook(data->mlx_win, 2, 0, key_handler, data);
    mlx_hook(data->mlx_win, 3, 0, key_exit, data);
    mlx_hook(data->mlx_win, 17, 0, free_exit, data);
    printf("--->%d %d \n", ((t_item *)data->map->item->content)->px, ((t_item *)data->map->item->content)->py);
	mlx_loop_hook(data->mlx, launch_game, data);
	mlx_loop(data->mlx);
}