/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:31:39 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/21 15:35:17 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_sprite(t_data *data, int y)
{
	int	i;
	int	j;

	j = data->img[data->t->n_frame]->s_line * data->sp->texY + \
		data->sp->texX * data->img[data->t->n_frame]->bt / 8;
	if (data->img[data->t->n_frame]->p_img[j] == 0 && \
		data->img[data->t->n_frame]->p_img[j + 1] == 0 && \
			data->img[data->t->n_frame]->p_img[j + 2] == 0)
		return ;
	i = data->sp->stripe * data->img[0]->bt / 8 + data->img[0]->s_line * y;
	data->img[0]->p_img[i] = data->img[data->t->n_frame]->p_img[j];
	data->img[0]->p_img[++i] = data->img[data->t->n_frame]->p_img[++j];
	data->img[0]->p_img[++i] = data->img[data->t->n_frame]->p_img[++j];
}

void	put_spirtes(t_data *data)
{
	t_list	*tmp;
	t_item	*content;

	tmp = data->map->item;
	while (tmp)
	{
		content = (t_item *)tmp->content;
		if (content->py == (int)data->pl->posX && \
			content->px == (int)data->pl->posY)
		{
			data->n_taken++;
			content->px = -1;
			content->py = -1;
		}
		if (!(content->px == -1 && content->py == -1))
			draw_sprites(data, ((double)(content)->py) + \
				0.5, (double)(content)->px + 0.5);
		tmp = tmp->next;
	}
}

void	timer_and_calc(t_data *data, double x, double y)
{
	clock_t	end;
	double	time;

	end = clock();
	time = (double)(end - data->t->start) / CLOCKS_PER_SEC;
	if (data->t->n_frame == 12)
		data->t->n_frame = 6;
	if ((int)(ceil(time)) % 1 == 0 && data->t->n_frame != 12)
	{
		if (data->t->tmp != (int)(ceil(time)))
		{
			data->t->n_frame++;
			data->t->tmp = (int)(ceil(time));
		}
	}
	data->sp->invDet = 1.0 / (data->pl->plX * data->pl->dirY - \
		data->pl->dirX * data->pl->plY);
	data->sp->transfX = (1.0 / (data->pl->plX * data->pl->dirY - data->pl->dirX \
		* data->pl->plY)) * (data->pl->dirY * (x - data->pl->posX) \
			- data->pl->dirX * (y - data->pl->posY));
}

void	calc(t_data *data, double x, double y)
{
	data->sp->transfY = (1.0 / (data->pl->plX * data->pl->dirY - data->pl->dirX \
		* data->pl->plY)) * (-data->pl->plY * (x - data->pl->posX) \
			+ data->pl->plX * (y - data->pl->posY));
	data->sp->vmovescreen = 120 / data->sp->transfY;
	data->sp->spriteScreenX = (int)((screenWidth / 2) * \
		(1 + data->sp->transfX / data->sp->transfY));
	data->sp->spriteHeight = abs((int)(screenHeight / (data->sp->transfY))) / 3;
	data->sp->drawStartY = -data->sp->spriteHeight / 2 + \
		screenHeight / 2 + data->sp->vmovescreen;
	if (data->sp->drawStartY < 0)
		data->sp->drawStartY = 0;
	data->sp->drawEndY = data->sp->spriteHeight / 2 + \
		screenHeight / 2 + data->sp->vmovescreen;
	if (data->sp->drawEndY >= screenHeight)
		data->sp->drawEndY = screenHeight - 1;
	data->sp->spriteWidth = abs((int)(screenHeight / (data->sp->transfY))) / 3;
	data->sp->drawStartX = -data->sp->spriteWidth / 2 + data->sp->spriteScreenX;
	if (data->sp->drawStartX < 0)
		data->sp->drawStartX = 0;
	data->sp->drawEndX = data->sp->spriteWidth / 2 + data->sp->spriteScreenX;
	if (data->sp->drawEndX >= screenWidth)
		data->sp->drawEndX = screenWidth - 1;
	data->sp->stripe = data->sp->drawStartX;
}

void	draw_sprites(t_data *data, double x, double y)
{
	int		d;

	timer_and_calc(data, x, y);
	calc(data, x, y);
	while (++data->sp->stripe < data->sp->drawEndX)
	{
		data->sp->texX = (int)(256 * (data->sp->stripe - \
			(-data->sp->spriteWidth / 2 + data->sp->spriteScreenX)) \
				* data->img[data->t->n_frame]->width / \
				data->sp->spriteWidth) / 256;
		if (data->sp->transfY > 0 && data->sp->stripe > 0 && \
		data->sp->stripe < screenWidth && data->sp->transfY \
		< data->sp->buffer[data->sp->stripe])
		{
			y = data->sp->drawStartY;
			while (++y < data->sp->drawEndY)
			{
				d = (y - data->sp->vmovescreen) * 256 - screenHeight \
					* 128 + data->sp->spriteHeight * 128;
				data->sp->texY = ((d * data->img[data->t->n_frame]->height) \
					/ data->sp->spriteHeight) / 256;
				put_sprite(data, y);
			}
		}
	}
}
