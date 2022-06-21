/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:39:20 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/21 18:19:29 by jdecorte         ###   ########.fr       */
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

void	trace_line(t_img *img, int color, t_data *data)
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
		if (data->x0 < 1000 && data->y0 < 800 && data->x0 > 0 && data->y0 > 0)
			put_pxl(img, data->x0, data->y0, color);
		data->x0 += x_step;
		data->y0 += y_step;
	}
}
