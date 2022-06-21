/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:42:00 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/21 09:42:01 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

void	draw_verttext(t_data *data, int x, int y, t_img *text)
{
	int	i;
	int	j;

	i = x * data->img[0]->bt / 8 + data->img[0]->s_line * y;
	j = data->dda->textx * (text->bt / 8) + data->dda->texty * text->s_line;

	data->img[0]->p_img[i] = text->p_img[j];
	data->img[0]->p_img[++i] = text->p_img[++j];
	data->img[0]->p_img[++i] = text->p_img[++j];
}

void	set_texture(t_data *p)
{
	if (p->dda->side == 1 || p->dda->side == 2 || p->dda->side == 6)
	{
		p->dda->wallx = p->pl->posY + p->dda->walldist * p->dda->raydir_y;
		p->dda->wallx -= floor(p->dda->wallx);
		p->dda->textx = (int)(p->dda->wallx
				* (double)p->img[p->dda->side]->width);
		if (p->dda->raydir_x > 0)
			p->dda->textx = p->img[p->dda->side]->width - p->dda->textx - 1;
	}
	else if (p->dda->side == 3 || p->dda->side == 4 || p->dda->side == 6)
	{
		p->dda->wallx = p->pl->posX + p->dda->walldist * p->dda->raydir_x;
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

	i = 0;
	set_texture(p);
	p->dda->step = 1.0 * p->img[p->dda->side]->height / p->dda->lineheight;
	p->dda->textpos = (p->dda->drawstart - screenHeight / 2
			+ p->dda->lineheight / 2) * p->dda->step;
	while (y < p->dda->drawend)
	{
		p->dda->texty = (int)p->dda->textpos
			& (p->img[p->dda->side]->height - 1);
		p->dda->textpos += p->dda->step;
		draw_verttext(p, p->dda->screenx, y, p->img[p->dda->side]);
		y++;
		i++;
	}
	return (i);
}

void	run_draw(t_data *data)
{
	int	y;

	y = 0;
	data->dda->lineheight = (int)(screenHeight / data->dda->walldist);
	data->dda->drawstart = -data->dda->lineheight / 2 + screenHeight / 2;
	if (data->dda->drawstart < 0)
		data->dda->drawstart = 0;
	data->dda->drawend = data->dda->lineheight / 2 + screenHeight / 2;
	if (data->dda->drawend > screenHeight)
		data->dda->drawend = screenHeight - 1;
	y += draw_vertline(data, data->dda->screenx,
			data->dda->drawstart, data->map->C, 0);
	y += draw_texture(data, y);
	draw_vertline(data, data->dda->screenx, screenHeight, data->map->F, y);
}
