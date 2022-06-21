/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 22:34:59 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/21 10:28:50 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	map_init(t_map *map, t_data *data)
{
	map->spawn = 0;
	map->item = 0;
	data->t->start = clock();
	data->t->n_frame = 6;
	data->map = map;
	data->t->tmp = 1;
	data->pl->totalrots = 0;
}

int	launch_game(t_data *data)
{
	void	*img;

	img = mlx_new_image(data->mlx, screenWidth, screenHeight);
	data->img[0]->p_img = mlx_get_data_addr(img, &data->img[0]->bt, \
			&data->img[0]->s_line, &data->img[0]->endian);
	mlx_hook(data->mlx_win, 2, 0, key_handler, data);
	mousing(data);
	update_param(data, data->pl->rot);
	raycaster(data);
	draw_bg(data);
	minimap(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, img, 0, 0);
	return (0);
}

int	free_exit(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_map	map;

	if (ac == 1)
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	init_data(data);
	map_init(&map, data);
	if (parsing(data, &map, av))
		exit (0);
	set_spawn(data);
	set_plane(data, data->map->dirSpawn);
	mlx_mouse_hide();
	mlx_do_key_autorepeaton(data->mlx);
	mlx_hook(data->mlx_win, 2, 0, key_handler, data);
	mlx_hook(data->mlx_win, 3, 0, key_exit, data);
	mlx_hook(data->mlx_win, 17, 0, free_exit, data);
	mlx_loop_hook(data->mlx, launch_game, data);
	mlx_loop(data->mlx);
}
