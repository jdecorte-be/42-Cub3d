/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 22:28:39 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/21 18:05:59 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	key_exit(int key, t_data *data)
{
	if (key == 123)
		data->pl->rot = 0;
	if (key == 124)
		data->pl->rot = 0;
	if (key == 123)
		data->pl->rot = 0;
	if (key == 124)
		data->pl->rot = 0;
	if (key == 13)
		data->pl->dey = 0;
	if (key == 1)
		data->pl->dey = 0;
	if (key == 2)
		data->pl->dex = 0;
	if (key == 0)
		data->pl->dex = 0;
	return (0);
}

void	set_dir(t_data *ptr, char flag)
{
	if (flag == 'W')
	{
		ptr->pl->dirx = 1;
		ptr->pl->diry = -1;
	}
	else if (flag == 'E')
	{
		ptr->pl->dirx = 1;
		ptr->pl->diry = 1;
	}
	else if (flag == 'N')
	{
		ptr->pl->diry = 1;
		ptr->pl->dirx = -1;
	}
	else if (flag == 'S')
	{
		ptr->pl->diry = 1;
		ptr->pl->dirx = 1;
	}
}

void	key_dir(t_data *data)
{
	if (data->map->map[(int)(data->pl->posx - 1.0)] \
			[(int)(data->pl->posy)] == 'D')
		data->map->map[(int)(data->pl->posx - 1.0 + data->pl->dirx \
			* data->pl->dey)][(int)(data->pl->posy)] = '0';
	else if (data->map->map[(int)(data->pl->posx + 1.0)] \
			[(int)(data->pl->posy)] == 'D')
		data->map->map[(int)(data->pl->posx + 1.0 + data->pl->dirx \
			* data->pl->dey)][(int)(data->pl->posy)] = '0';
	else if (data->map->map[(int)(data->pl->posx)] \
			[(int)(data->pl->posy + 1.0)] == 'D')
		data->map->map[(int)(data->pl->posx + data->pl->dirx \
				* data->pl->dey)][(int)(data->pl->posy + 1.0)] = '0';
	else if (data->map->map[(int)(data->pl->posx)] \
			[(int)(data->pl->posy - 1.0)] == 'D')
		data->map->map[(int)(data->pl->posx + data->pl->dirx * \
				data->pl->dey)][(int)(data->pl->posy - 1.0)] = '0';
}

void	spawn_changer(int key, t_data *data)
{
	if (key == 126)
	{
		pl_init(data);
		data->map->spawn = data->map->spawn->next;
		set_spawn(data);
		set_plane(data, data->map->dirspawn);
	}
	if (key == 125)
	{
		pl_init(data);
		data->map->spawn = data->map->spawn->prev;
		set_spawn(data);
		set_plane(data, data->map->dirspawn);
	}
}

int	key_handler(int key, t_data *data)
{
	if (key == 53)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	if (key == 14)
		key_dir(data);
	if (key == 13)
		data->pl->dey = 0.1;
	if (key == 1)
		data->pl->dey = -0.1;
	if (key == 2)
		data->pl->dex = 0.1;
	if (key == 0)
		data->pl->dex = -0.1;
	if (key == 123)
		data->pl->rot = 0.1;
	if (key == 124)
		data->pl->rot = -0.1;
	spawn_changer(key, data);
	return (0);
}
