/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 22:11:18 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/21 17:00:18 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	is_side_door(t_data *ptr)
{
	ptr->dda->hit = 1;
	if (!ptr->dda->side)
	{
		if (ptr->dda->raydir_x < 0)
			ptr->dda->side = 5;
		else if (ptr->dda->raydir_x > 0)
			ptr->dda->side = 2;
	}
	else if (ptr->dda->side == 1)
	{
		if (ptr->dda->raydir_y < 0)
			ptr->dda->side = 3;
		else if (ptr->dda->raydir_y > 0)
			ptr->dda->side = 4;
	}
}

void	is_side(t_data *ptr)
{
	ptr->dda->hit = 1;
	if (!ptr->dda->side)
	{
		if (ptr->dda->raydir_x < 0)
			ptr->dda->side = 1;
		else if (ptr->dda->raydir_x > 0)
			ptr->dda->side = 2;
	}
	else if (ptr->dda->side == 1)
	{
		if (ptr->dda->raydir_y < 0)
			ptr->dda->side = 3;
		else if (ptr->dda->raydir_y > 0)
			ptr->dda->side = 4;
	}
}

void	check_dist_step(t_data *ptr)
{
	if (ptr->dda->sidedist_x < ptr->dda->sidedist_y)
	{
		ptr->dda->sidedist_x += ptr->dda->deltadist_x;
		ptr->dda->map_x += ptr->dda->stepx;
		ptr->dda->side = 0;
	}
	else
	{
		ptr->dda->sidedist_y += ptr->dda->deltadist_y;
		ptr->dda->map_y += ptr->dda->stepy;
		ptr->dda->side = 1;
	}
	if (ptr->map->map[ptr->dda->map_x][ptr->dda->map_y] == '1')
		is_side(ptr);
	if (ptr->map->map[ptr->dda->map_x][ptr->dda->map_y] == 'D')
		is_side_door(ptr);
}

void	check_dist(t_data *ptr)
{
	ptr->dda->hit = 0;
	ptr->dda->side = 0;
	while (ptr->dda->hit == 0)
		check_dist_step(ptr);
	if (ptr->dda->side == 1 || ptr->dda->side == 2 || ptr->dda->side == 6)
		ptr->dda->walldist = (ptr->dda->map_x - ptr->pl->posx + \
			(1 - ptr->dda->stepx) / 2) / ptr->dda->raydir_x;
	else if (ptr->dda->side == 3 || ptr->dda->side == 4 || ptr->dda->side == 6)
		ptr->dda->walldist = (ptr->dda->map_y - ptr->pl->posY + \
			(1 - ptr->dda->stepy) / 2) / ptr->dda->raydir_y;
}

void	check_side(t_data *ptr)
{
	if (ptr->dda->raydir_x < 0)
	{
		ptr->dda->stepx = -1;
		ptr->dda->sidedist_x = (ptr->pl->posx - \
			ptr->dda->map_x) * ptr->dda->deltadist_x;
	}
	else
	{
		ptr->dda->stepx = 1;
		ptr->dda->sidedist_x = (ptr->dda->map_x + 1.0 - \
			ptr->pl->posx) * ptr->dda->deltadist_x;
	}
	if (ptr->dda->raydir_y < 0)
	{
		ptr->dda->stepy = -1;
		ptr->dda->sidedist_y = (ptr->pl->posY - \
			ptr->dda->map_y) * ptr->dda->deltadist_y;
	}
	else
	{
		ptr->dda->stepy = 1;
		ptr->dda->sidedist_y = (ptr->dda->map_y + 1.0 - \
			ptr->pl->posY) * ptr->dda->deltadist_y;
	}
}
