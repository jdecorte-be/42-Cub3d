/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:41:15 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/21 09:41:38 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	mousing(t_data *data)
{
	static int	mx;
	int			x;
	int			y;
	double		olddirx;
	int			dx;

	mx = mx - 1;
	if (mx == -1)
		mx = x;
	mlx_mouse_get_pos(data->mlx_win, &x, &y);
	dx = x - screenWidth / 2;
	if (dx > 0)
		update_param(data, dx * (-ROTX));
	else if (dx < 0)
		update_param(data, -dx * ROTX);
	mlx_mouse_move(data->mlx_win, screenWidth / 2, screenHeight / 2);
	return (0);
}

void	update_param(t_data *data, double rot)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->pl->dirX;
	data->pl->totalrots += rot;
	data->pl->dirX = data->pl->dirX * cos(rot) - data->pl->dirY * sin(rot);
	data->pl->dirY = olddirx * sin(rot) + data->pl->dirY * cos(rot);
	oldplanex = data->pl->plX;
	data->pl->plX = data->pl->plX * cos(rot) - data->pl->plY * sin(rot);
	data->pl->plY = oldplanex * sin(rot) + data->pl->plY * cos(rot);
	if (!ft_strchr("1D", data->map->map[(int)(data->pl->posX + \
			data->pl->dirX * data->pl->deY)][(int)(data->pl->posY)]))
		data->pl->posX += data->pl->dirX * data->pl->deY;
	if (!ft_strchr("1D", data->map->map[(int)(data->pl->posX)] \
			[(int)(data->pl->posY + data->pl->dirY * data->pl->deY)]))
		data->pl->posY += data->pl->dirY * data->pl->deY;
	if (!ft_strchr("1D", data->map->map[(int)(data->pl->posX + \
			data->pl->plX * data->pl->deX)][(int)data->pl->posY]))
		data->pl->posX += data->pl->plX * data->pl->deX;
	if (!ft_strchr("1D", data->map->map[(int)data->pl->posX] \
			[(int)(data->pl->posY + data->pl->plY * data->pl->deX)]))
		data->pl->posY += data->pl->plY * data->pl->deX;
}
