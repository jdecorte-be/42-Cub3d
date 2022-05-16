#include "../inc/cub3d.h"

void			is_side_door(t_data *ptr)
{
	ptr->dda->hit = 1;
	if (!ptr->dda->side)
	{
		if (ptr->dda->raydir_x < 0)
			ptr->dda->side = 6;
		else if (ptr->dda->raydir_x > 0)
			ptr->dda->side = 6;
	}
	else if (ptr->dda->side == 1)
	{
		if (ptr->dda->raydir_y < 0)
			ptr->dda->side = 6;
		else if (ptr->dda->raydir_y > 0)
			ptr->dda->side = 6;
	}
}

void			is_side(t_data *ptr)
{
	ptr->dda->hit = 1;
	if (!ptr->dda->side)
	{
		if (ptr->dda->raydir_x < 0)
			ptr->dda->side = 1;
		else if (ptr->dda->raydir_x > 0)
			ptr->dda->side = 2;
	}
	else if (ptr->dda->side == 1)
	{
		if (ptr->dda->raydir_y < 0)
			ptr->dda->side = 3;
		else if (ptr->dda->raydir_y > 0)
			ptr->dda->side = 4;
	}
}

// OK
void			check_dist(t_data *ptr)
{
	ptr->dda->hit = 0;
	ptr->dda->side = 0;
	while (ptr->dda->hit == 0)
	{
		if (ptr->dda->sidedist_x < ptr->dda->sidedist_y)
		{
			ptr->dda->sidedist_x += ptr->dda->deltadist_x;
			ptr->dda->map_x += ptr->dda->stepx;
			ptr->dda->side = 0;
		}
		else
		{
			ptr->dda->sidedist_y += ptr->dda->deltadist_y;
			ptr->dda->map_y += ptr->dda->stepy;
			ptr->dda->side = 1;
		}
		if (ptr->map->map[ptr->dda->map_x][ptr->dda->map_y] == '1')
			is_side(ptr);
		if (ptr->map->map[ptr->dda->map_x][ptr->dda->map_y] == 'D')
			is_side(ptr);
	}
	if (ptr->dda->side == 1 || ptr->dda->side == 2)
		ptr->dda->walldist = (ptr->dda->map_x - ptr->pl->posX + (1 - ptr->dda->stepx) / 2) / ptr->dda->raydir_x;
	else if (ptr->dda->side == 3 || ptr->dda->side == 4)
		ptr->dda->walldist = (ptr->dda->map_y - ptr->pl->posY + (1 - ptr->dda->stepy) / 2) / ptr->dda->raydir_y;
}

void			check_side(t_data *ptr)
{
	if (ptr->dda->raydir_x < 0)
	{
		ptr->dda->stepx = -1;
		ptr->dda->sidedist_x = (ptr->pl->posX - ptr->dda->map_x) * ptr->dda->deltadist_x;
	}
	else
	{
		ptr->dda->stepx = 1;
		ptr->dda->sidedist_x = (ptr->dda->map_x + 1.0 - ptr->pl->posX) * ptr->dda->deltadist_x;
	}
	if (ptr->dda->raydir_y < 0)
	{
		ptr->dda->stepy = -1;
		ptr->dda->sidedist_y = (ptr->pl->posY - ptr->dda->map_y) * ptr->dda->deltadist_y;
	}
	else
	{
		ptr->dda->stepy = 1;
		ptr->dda->sidedist_y = (ptr->dda->map_y + 1.0 - ptr->pl->posY) * ptr->dda->deltadist_y;
	}
}

// fov 
void			calc_dda(t_data *ptr)
{
	ptr->dda->cam_x = 2 * (double)ptr->dda->screenx / (double)screenWidth - 1;
	ptr->dda->raydir_x = ptr->pl->dirX + ptr->pl->plX * ptr->dda->cam_x;
	ptr->dda->raydir_y = ptr->pl->dirY + ptr->pl->plY * ptr->dda->cam_x;
	ptr->dda->map_x = (int)ptr->pl->posX;
	ptr->dda->map_y = (int)ptr->pl->posY;
	ptr->dda->deltadist_x = fabs(1 / ptr->dda->raydir_x);
	ptr->dda->deltadist_y = fabs(1 / ptr->dda->raydir_y);
	check_side(ptr);
	check_dist(ptr);
}

void    raycaster(t_data *data)
{
	data->dda->screenx = 0;
	while (data->dda->screenx < screenWidth)
	{
		calc_dda(data);
		run_draw(data);
		data->sp->buffer[data->dda->screenx] = data->dda->walldist;
		data->dda->screenx++;
	}
	// update_fps(data);
	draw_sprites(data, 2, 2);
	// draw_door(data, 2, 2);
}