/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:42:00 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/25 19:12:54 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <math.h>

int			get_texture_color(t_img *img, int x, int y)
{
	if (x >= 0 && x < WIN_WIDTH
		&& y >= 0 && y < WIN_HEIGHT)
	{
		return (*(int*)(img->p_img
			+ (4 * img->width * (int)y)
			+ (4 * (int)x)));
	}
	return (0x0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	if (x >= 0 && x < WIN_WIDTH
		&& y >= 0 && y < WIN_HEIGHT)
		*(int*)(img->p_img
			+ (4 * (int)WIN_WIDTH * (int)y)
			+ ((int)x * 4)) = color;
}

int	draw_vertline(t_data *data, int x, int y, int color, int j)
{
	int	i;

	while (j < y)
	{
		i = (x * data->img[0]->bt / 8) + (j * data->img[0]->s_line);
		data->img[0]->p_img[i] = color;
		data->img[0]->p_img[++i] = color >> 8;
		data->img[0]->p_img[++i] = color >> 16;
		j++;
	}
	return (j);
}

void	set_texture(t_data *p)
{
	if (p->dda->side == 1 || p->dda->side == 2 || p->dda->side == 13 || p->dda->side == 14)
	{
		p->dda->wallx = p->pl->posy + p->dda->walldist * p->dda->raydir_y;
		p->dda->wallx -= floor(p->dda->wallx);
		p->dda->textx = (int)(p->dda->wallx
				* (double)p->img[p->dda->side]->width) % p->img[p->dda->side]->width;
		if (p->dda->raydir_x > 0)
			p->dda->textx = p->img[p->dda->side]->width - p->dda->textx - 1;
	}
	else if (p->dda->side == 3 || p->dda->side == 4 || p->dda->side == 15 || p->dda->side == 16)
	{
		p->dda->wallx = p->pl->posx + p->dda->walldist * p->dda->raydir_x;
		p->dda->wallx -= floor(p->dda->wallx);
		p->dda->textx = (int)(p->dda->wallx
				* (double)p->img[p->dda->side]->width) % p->img[p->dda->side]->width;
		if (p->dda->raydir_y < 0)
			p->dda->textx = p->img[p->dda->side]->width - p->dda->textx - 1;
	}
}

int	draw_texture(t_data *p, int y)
{
	int	i;

	i = 0;
	int color;
	set_texture(p);
	p->dda->step = 1.0 * p->img[p->dda->side]->height / p->dda->lineheight;
	p->dda->textpos = (p->dda->drawstart - WIN_HEIGHT / 2
			+ p->dda->lineheight / 2) * p->dda->step;
	while (y < p->dda->drawend - 1)
	{
		p->dda->texty = (int)((y * 2 - WIN_HEIGHT + p->dda->lineheight)
				* ((p->img[p->dda->side]->height / 2.) / p->dda->lineheight));
		color = get_texture_color(p->img[p->dda->side], p->dda->textx, p->dda->texty);
		my_mlx_pixel_put(p->img[0], p->dda->screenx, y, color);
		// printf("%d / %d\n", p->dda->texty, p->dda->lineheight);
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
	y += draw_vertline(data, data->dda->screenx,
			data->dda->drawstart, data->map->c, 0);
	y += draw_texture(data, y);
	draw_vertline(data, data->dda->screenx, WIN_HEIGHT, data->map->f, y);
}
