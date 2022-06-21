/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:08:14 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/21 18:20:36 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	trace_line_wall(t_img *img, int color, t_data *data)
{
	float	x_step;
	float	y_step;
	int		max;

	x_step = data->x1 - data->x0;
	y_step = data->y1 - data->y0;
	max = find_max(find_mod(x_step), find_mod(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(data->x0 - data->x1) || (int)(data->y0 - data->y1))
	{
		if (data->x0 < 200 && data->y0 < 200 && data->x0 > 10 && data->y0 > 10)
			put_pxl(img, data->x0, data->y0, color);
		data->x0 += x_step;
		data->y0 += y_step;
	}
}

void	draw_wall(t_data *data, double x, double y, int color)
{
	double	i;

	i = y;
	while (i < y + 30)
	{
		data->x0 = x;
		data->x1 = x + 30;
		data->y0 = i;
		data->y1 = i;
		trace_line_wall(data->img[0], color, data);
		i += 1;
	}
}

void	draw_spawn(t_data *data, double x, double y)
{
	double	i;

	i = y;
	while (i < y + 10)
	{
		data->x0 = x;
		data->y0 = i;
		data->x1 = x + 10;
		data->y1 = i;
		trace_line(data->img[0], 0xDC143C, data);
		i += 1;
	}
}

void	draw_bg(t_data *data)
{
	double	i;

	i = 10;
	while (i < 200)
	{
		data->x0 = 10;
		data->y0 = i;
		data->x1 = 200;
		data->y1 = i;
		trace_line(data->img[0], 0xE1D5C8, data);
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
				draw_wall(data, (y - data->pl->posy) * 30 + 105, \
					(x - data->pl->posx) * 30 + 105, 0xB85E4F);
			if (data->map->map[x][y] == 'D')
				draw_wall(data, (y - data->pl->posy) * 30 + 105, \
					(x - data->pl->posx) * 30 + 105, 0x4C3232);
			y++;
		}
		x++;
	}
	data->x0 = 10;
	data->y0 = 10;
	data->x1 = 200;
	data->y1 = 10;
	trace_line(data->img[0], 0x4C3232, data);
	data->x0 = 10;
	data->y0 = 10;
	data->x1 = 10;
	data->y1 = 200;
	trace_line(data->img[0], 0x4C3232, data);
	data->x0 = 200;
	data->y0 = 10;
	data->x1 = 200;
	data->y1 = 200;
	trace_line(data->img[0], 0x4C3232, data);
	data->x0 = 10;
	data->y0 = 200;
	data->x1 = 200;
	data->y1 = 200;
	trace_line(data->img[0], 0x4C3232, data);
	draw_spawn(data, 100, 100);
}
