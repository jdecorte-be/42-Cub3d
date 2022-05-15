#include "../inc/cub3d.h"

int				draw_ceilling(t_data *p, int y)
{
	int r;
	int g;
	int b;

	r = 80 % 256; // change color
	g = (80 / 256) % 256;
	b = ((80 / 256) / 256) % 256;
	while (y < p->dda->drawstart)
	{
		p->img[0]->p_img[p->dda->screenx * p->img[0]->bt / 8 + p->img[0]->s_line * y] = r;
		p->img[0]->p_img[(p->dda->screenx * p->img[0]->bt / 8 + p->img[0]->s_line * y) + 1] = g;
		p->img[0]->p_img[(p->dda->screenx * p->img[0]->bt / 8 + p->img[0]->s_line * y) + 2] = b;
		y++;
	}
	return (y);
}

void			set_texture(t_data *p)
{
	if (p->dda->side == 1 || p->dda->side == 2)
	{
		p->dda->wallx = p->pl->posY + p->dda->walldist * p->dda->raydir_y;
		p->dda->wallx -= floor(p->dda->wallx);
		p->dda->textx = (int)(p->dda->wallx * (double)p->img[p->dda->side]->
		width);
		if (p->dda->raydir_x > 0)
			p->dda->textx = p->img[p->dda->side]->width - p->dda->textx - 1;
	}
	else if (p->dda->side == 3 || p->dda->side == 4)
	{
		p->dda->wallx = p->pl->posX + p->dda->walldist * p->dda->raydir_x;
		p->dda->wallx -= floor(p->dda->wallx);
		p->dda->textx = (int)(p->dda->wallx * (double)p->img[p->dda->side]->
		width);
		if (p->dda->raydir_y < 0)
			p->dda->textx = p->img[p->dda->side]->width - p->dda->textx - 1;
	}
}

void		put_pixel_texture(t_data *p, int y)
{
	p->img[0]->p_img[p->dda->screenx * p->img[0]->bt / 8 + p->img[0]->s_line * y]
	= p->img[p->dda->side]->p_img[p->dda->textx * (p->img
	[p->dda->side]->bt / 8) + p->dda->texty * p->img[p->dda->side]->s_line];

	p->img[0]->p_img[(p->dda->screenx * p->img[0]->bt / 8 + p->img[0]->
	s_line * y) + 1] = p->img[p->dda->side]->p_img[(p->dda->textx *
	(p->img[p->dda->side]->bt / 8) + p->dda->texty * p->img
	[p->dda->side]->s_line) + 1];

	p->img[0]->p_img[(p->dda->screenx * p->img[0]->bt / 8 + p->img[0]->
	s_line * y) + 2] = p->img[p->dda->side]->p_img[(p->dda->textx *
	(p->img[p->dda->side]->bt / 8) + p->dda->texty * p->img[p->dda->side]->
	s_line) + 2];
}

int				draw_texture(t_data *p, int y)
{
	int i;

	i = 0;
	set_texture(p);
	p->dda->step = 1.0 * p->img[p->dda->side]->height / p->dda->lineheight;
	p->dda->textpos = (p->dda->drawstart - screenHeight / 2 + p->dda->lineheight
	/ 2) * p->dda->step;
	while (y < p->dda->drawend)
	{
		p->dda->texty = (int)p->dda->textpos & (p->img[p->dda->side]->height
		- 1);
		p->dda->textpos += p->dda->step;
		put_pixel_texture(p, y);
		y++;
		i++;
	}
	return (i);
}

void			run_draw(t_data *data)
{
	int y;

	y = 0;
	data->dda->lineheight = (int)(screenHeight / data->dda->walldist);
	data->dda->drawstart = -data->dda->lineheight / 2 + screenHeight / 2;
	if (data->dda->drawstart < 0)
		data->dda->drawstart = 0;
	data->dda->drawend = data->dda->lineheight / 2 + screenHeight / 2;
	if (data->dda->drawend > screenHeight)
		data->dda->drawend = screenHeight - 1;
	y += draw_ceilling(data, y);
	y += draw_texture(data, y);
	// draw_floor(data, y);
}