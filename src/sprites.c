/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:31:39 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/21 17:07:51 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_sprite(t_data *data, int y)
{
	int	i;
	int	j;

	j = data->img[data->t->n_frame]->s_line * data->sp->texy + \
		data->sp->texx * data->img[data->t->n_frame]->bt / 8;
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
		if (content->py == (int)data->pl->posx && \
			content->px == (int)data->pl->posy)
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
	data->sp->invdet = 1.0 / (data->pl->plx * data->pl->diry - \
		data->pl->dirx * data->pl->ply);
	data->sp->transfx = (1.0 / (data->pl->plx * data->pl->diry - data->pl->dirx \
		* data->pl->ply)) * (data->pl->diry * (x - data->pl->posx) \
			- data->pl->dirx * (y - data->pl->posy));
}

void	calc(t_data *data, double x, double y)
{
	data->sp->transfy = (1.0 / (data->pl->plx * data->pl->diry - data->pl->dirx \
		* data->pl->ply)) * (-data->pl->ply * (x - data->pl->posx) \
			+ data->pl->plx * (y - data->pl->posy));
	data->sp->vmovescreen = 120 / data->sp->transfy;
	data->sp->spritescreenx = (int)((WIN_WIDTH / 2) * \
		(1 + data->sp->transfx / data->sp->transfy));
	data->sp->spriteheight = abs((int)(WIN_HEIGHT / (data->sp->transfy))) / 3;
	data->sp->drawstarty = -data->sp->spriteheight / 2 + \
		WIN_HEIGHT / 2 + data->sp->vmovescreen;
	if (data->sp->drawstarty < 0)
		data->sp->drawstarty = 0;
	data->sp->drawendy = data->sp->spriteheight / 2 + \
		WIN_HEIGHT / 2 + data->sp->vmovescreen;
	if (data->sp->drawendy >= WIN_HEIGHT)
		data->sp->drawendy = WIN_HEIGHT - 1;
	data->sp->spritewidth = abs((int)(WIN_HEIGHT / (data->sp->transfy))) / 3;
	data->sp->drawstartx = -data->sp->spritewidth / 2 + data->sp->spritescreenx;
	if (data->sp->drawstartx < 0)
		data->sp->drawstartx = 0;
	data->sp->drawendx = data->sp->spritewidth / 2 + data->sp->spritescreenx;
	if (data->sp->drawendx >= WIN_WIDTH)
		data->sp->drawendx = WIN_WIDTH - 1;
	data->sp->stripe = data->sp->drawstartx;
}

void	draw_sprites(t_data *data, double x, double y)
{
	int		d;

	timer_and_calc(data, x, y);
	calc(data, x, y);
	while (++data->sp->stripe < data->sp->drawendx)
	{
		data->sp->texx = (int)(256 * (data->sp->stripe - \
			(-data->sp->spritewidth / 2 + data->sp->spritescreenx)) \
				* data->img[data->t->n_frame]->width / \
				data->sp->spritewidth) / 256;
		if (data->sp->transfy > 0 && data->sp->stripe > 0 && \
		data->sp->stripe < WIN_WIDTH && data->sp->transfy \
		< data->sp->buffer[data->sp->stripe])
		{
			y = data->sp->drawstarty;
			while (++y < data->sp->drawendy)
			{
				d = (y - data->sp->vmovescreen) * 256 - WIN_HEIGHT \
					* 128 + data->sp->spriteheight * 128;
				data->sp->texy = ((d * data->img[data->t->n_frame]->height) \
					/ data->sp->spriteheight) / 256;
				put_sprite(data, y);
			}
		}
	}
}
