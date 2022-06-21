/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:39:20 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/21 17:00:45 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_error(void *arg, int e)
{
	if (e == 2)
		write (2, "malloc\n", 7);
	else if (e == 9)
		write (2, "map error\n", 10);
	exit (1);
}

void	set_spawn(t_data *data)
{
	data->map->dirspawn = ((t_item *)(data->map->spawn->content))->type;
	data->pl->posx = ((t_item *)(data->map->spawn->content))->py + 0.5;
	data->pl->posy = ((t_item *)(data->map->spawn->content))->px + 0.5;
}

void	trace_line(float x0, float y0, float x1, float y1,t_img *img, int color)
{
	float	x_step;
	float	y_step;
	int		max;

	x_step = x1 - x0;
	y_step = y1 - y0;
	max = find_max(find_mod(x_step), find_mod(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(x0 - x1) || (int)(y0 - y1))
	{
		if (x0 < 1000 && y0 < 800 && x0 > 0 && y0 > 0)
			put_pxl(img, x0, y0, color);
		x0 += x_step;
		y0 += y_step;
	}
}
