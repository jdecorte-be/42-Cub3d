/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:08:14 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/21 15:27:15 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	trace_line_wall(float x0, float y0, float x1, float y1,t_img *img, int color)
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
		if (x0 < 200 && y0 < 200 && x0 > 10 && y0 > 10)
			put_pxl(img, x0, y0, color);
		x0 += x_step;
		y0 += y_step;
	}
}

void	draw_wall(t_data *data, double x, double y, int color)
{
	double	i;
	double	t_y;
	double	t_x;
	double	t_x2;
	double	t_y2;

	i = y;
	while (i < y + 30)
	{
		trace_line_wall(x, i, x + 30, i, data->img[0], color);
		i += 1;
	}
}

void	draw_spawn(t_data *data, double x, double y)
{
	double	i;

	i = y;
	while (i < y + 10)
	{
		trace_line(x, i, x + 10, i, data->img[0], 0xDC143C);
		i += 1;
	}
}

void	draw_bg(t_data *data)
{
	double	i;

	i = 10;
	while (i < 200)
	{
		trace_line(10, i, 200, i, data->img[0], 0xE1D5C8);
		i += 1;
	}
}

void	minimap(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->map->map[x])
	{
		y = 0;
		while (data->map->map[x][y])
		{
			if (data->map->map[x][y] == '1')
				draw_wall(data, (y - data->pl->posY) * 30 + 105, \
					(x - data->pl->posX) * 30 + 105, 0xB85E4F);
			if (data->map->map[x][y] == 'D')
				draw_wall(data, (y - data->pl->posY) * 30 + 105, \
					(x - data->pl->posX) * 30 + 105, 0x4C3232);
			y++;
		}
		x++;
	}
	trace_line(10, 10, 200, 10, data->img[0], 0x4C3232);
	trace_line(10, 10, 10, 200, data->img[0], 0x4C3232);
	trace_line(200, 10, 200, 200, data->img[0], 0x4C3232);
	trace_line(10, 200, 200, 200, data->img[0], 0x4C3232);
	draw_spawn(data, 100, 100);
}
