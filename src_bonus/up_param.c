/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:41:15 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/26 16:26:17 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	mousing(t_data *data)
{
	int			x;
	int			y;
	int			dx;

	mlx_mouse_get_pos(data->mlx_win, &x, &y);
	dx = x - WIN_WIDTH / 2;
	if (dx > 0)
		update_param(data, dx * (-(2 * M_PI / 11520)));
	else if (dx < 0)
		update_param(data, -dx * 2 * M_PI / 11520);
	mlx_mouse_move(data->mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (0);
}

void	update_param(t_data *data, double rot)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->pl->dirx;
	data->pl->totalrots += rot;
	data->pl->dirx = data->pl->dirx * cos(rot) - data->pl->diry * sin(rot);
	data->pl->diry = olddirx * sin(rot) + data->pl->diry * cos(rot);
	oldplanex = data->pl->plx;
	data->pl->plx = data->pl->plx * cos(rot) - data->pl->ply * sin(rot);
	data->pl->ply = oldplanex * sin(rot) + data->pl->ply * cos(rot);
	if (!ft_strchr("1D", data->map->map[(int)(data->pl->posx + \
			data->pl->dirx * data->pl->dey)][(int)(data->pl->posy)]))
		data->pl->posx += data->pl->dirx * data->pl->dey;
	if (!ft_strchr("1D", data->map->map[(int)(data->pl->posx)] \
			[(int)(data->pl->posy + data->pl->diry * data->pl->dey)]))
		data->pl->posy += data->pl->diry * data->pl->dey;
	if (!ft_strchr("1D", data->map->map[(int)(data->pl->posx + \
			data->pl->plx * data->pl->dex)][(int)data->pl->posy]))
		data->pl->posx += data->pl->plx * data->pl->dex;
	if (!ft_strchr("1D", data->map->map[(int)data->pl->posx] \
			[(int)(data->pl->posy + data->pl->ply * data->pl->dex)]))
		data->pl->posy += data->pl->ply * data->pl->dex;
}
