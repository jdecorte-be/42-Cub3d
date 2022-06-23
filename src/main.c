/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 22:34:59 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/23 13:10:16 by jdecorte42       ###   ########.fr       */
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
	data->n_taken = 0;
}

void	put_text(t_data *data)
{
	char	*str;
	char	*str2;
	char	*n;
	char	*n2;

	n = ft_itoa(data->n_taken);
	n2 = ft_itoa(data->n_sprites);
	str = ft_strjoin(n, " / ");
	str2 = ft_strjoin(str, n2);
	if (data->n_taken != data->n_sprites)
		mlx_string_put(data->mlx, data->mlx_win, 800, 650, 0xffffff, str2);
	else
		mlx_string_put(data->mlx, data->mlx_win, 700, 650, 0xffffff, \
			"Good Job You Have Finished!");
	free(str);
	free(str2);
	free(n);
	free(n2);
}

int	launch_game(t_data *data)
{
	void	*img;
	char	*str;

	img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->img[0]->p_img = mlx_get_data_addr(img, &data->img[0]->bt, \
			&data->img[0]->s_line, &data->img[0]->endian);
	mlx_hook(data->mlx_win, 2, 0, key_handler, data);
	mousing(data);
	update_param(data, data->pl->rot);
	raycaster(data);
	draw_bg(data);
	minimap(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, img, 0, 0);
	put_text(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_map	map;

	if (ac == 1)
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		exit (write_error("Error\nMalloc failed\n"));
	if (init_data(data))
		return (1);
	mlx_mouse_move(data->mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	map_init(&map, data);
	if (parsing(data, &map, av))
	{
		free_init_data(data);
		exit (1);
	}
	data->n_sprites = ft_lstsize(data->map->item);
	set_spawn(data);
	set_plane(data, data->map->dirspawn);
	mlx_mouse_hide();
	mlx_do_key_autorepeaton(data->mlx);
	mlx_hook(data->mlx_win, 2, 0, key_handler, data);
	mlx_hook(data->mlx_win, 3, 0, key_exit, data);
	mlx_hook(data->mlx_win, 17, 0, free_exit, data);
	mlx_loop_hook(data->mlx, launch_game, data);
	mlx_loop(data->mlx);
}
