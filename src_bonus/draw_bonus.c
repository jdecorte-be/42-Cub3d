/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:42:00 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/26 16:26:31 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <math.h>

int	get_pixel(t_img *img, int x, int y)
{
	int	*dst;
	int	color;

	dst = (void *)img->p_img + (y * img->s_line + x * \
		(img->bt / 8));
	color = *(int *)dst;
	return (color);
}

int	draw_vertline(t_data *data, int y, int color, int j)
{
	while (j < y)
	{
		my_mlx_pixel_put(data->img[0], data->dda->screenx, j, color);
		j++;
	}
	return (j);
}

void	set_texture(t_data *p)
{
	if (p->dda->side == 1 || p->dda->side == 2 || \
		p->dda->side == 13 || p->dda->side == 14)
	{
		p->dda->wallx = p->pl->posy + p->dda->walldist * p->dda->raydir_y;
		p->dda->wallx -= floor(p->dda->wallx);
		p->dda->textx = (int)(p->dda->wallx
				* (double)p->img[p->dda->side]->width);
		if (p->dda->raydir_x > 0)
			p->dda->textx = p->img[p->dda->side]->width - p->dda->textx - 1;
	}
	else if (p->dda->side == 3 || p->dda->side == 4 || \
		p->dda->side == 15 || p->dda->side == 16)
	{
		p->dda->wallx = p->pl->posx + p->dda->walldist * p->dda->raydir_x;
		p->dda->wallx -= floor(p->dda->wallx);
		p->dda->textx = (int)(p->dda->wallx
				* (double)p->img[p->dda->side]->width);
		if (p->dda->raydir_y < 0)
			p->dda->textx = p->img[p->dda->side]->width - p->dda->textx - 1;
	}
}

int	draw_texture(t_data *p, int y)
{
	int	i;
	int	color;

	i = 0;
	set_texture(p);
	p->dda->step = 1.0 * p->img[p->dda->side]->height / p->dda->lineheight;
	p->dda->textpos = (p->dda->drawstart - WIN_HEIGHT / 2
			+ p->dda->lineheight / 2) * p->dda->step;
	while (y < p->dda->drawend - 1)
	{
		p->dda->texty = (int)p->dda->textpos & \
			(p->img[p->dda->side]->height - 1);
		p->dda->textpos += p->dda->step;
		color = get_pixel(p->img[p->dda->side], p->dda->textx, p->dda->textpos);
		my_mlx_pixel_put(p->img[0], p->dda->screenx, y, color);
		y++;
		i++;
	}
	return (i);
}

void	run_draw(t_data *data)
{
	int	y;

	y = 0;
	data->dda->lineheight = (int)(WIN_HEIGHT / data->dda->walldist);
	data->dda->drawstart = -data->dda->lineheight / 2 + WIN_HEIGHT / 2;
	if (data->dda->drawstart < 0)
		data->dda->drawstart = 0;
	data->dda->drawend = data->dda->lineheight / 2 + WIN_HEIGHT / 2;
	if (data->dda->drawend > WIN_HEIGHT)
		data->dda->drawend = WIN_HEIGHT - 1;
	y += draw_vertline(data, data->dda->drawstart, \
		data->map->c, 0);
	y += draw_texture(data, y);
	draw_vertline(data, WIN_HEIGHT, data->map->f, y);
}
