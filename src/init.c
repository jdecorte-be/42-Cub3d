#include "../inc/cub3d.h"

void		set_plane(t_data *ptr, char flag)
{
	if (flag == 'W')
	{
		ptr->pl->plX = -0.66;
		ptr->pl->dirY = -1;
	}
	else if (flag == 'E')
	{
		ptr->pl->plX = 0.66;
		ptr->pl->dirY = 1;
	}
	else if (flag == 'N')
	{
		ptr->pl->plY = 0.66;
		ptr->pl->dirX = -1;
	}
	else if (flag == 'S')
	{
		ptr->pl->plY = -0.66;
		ptr->pl->dirX = 1;
	}
}

void	init_texture(t_data *ptr, int flag, char *path)
{
	ptr->img[flag]->p_img = mlx_xpm_file_to_image(ptr->mlx,
			path, &ptr->img[flag]->width, &ptr->img[flag]->height);
	if (!ptr->img[flag]->p_img)
		exit(write_error("Error\nMap load\n"));
	ptr->img[flag]->p_img = mlx_get_data_addr(ptr->img[flag]->p_img,
			&ptr->img[flag]->bt, &ptr->img[flag]->s_line,
			&ptr->img[flag]->endian);
}

void	init_data(t_data *data)
{
	int	i;

	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx,
			screenWidth, screenHeight, "cub3d");
	data->pl = malloc(sizeof(t_player));
	data->dda = malloc(sizeof(t_dda));
	data->map = malloc(sizeof(t_map));
	data->t = malloc(sizeof(t_time));
	if (!data->pl || !data->dda || !data->map || !data->t)
		return ;
	data->t->time = 0;
	data->t->oldtime = 0;
	i = 0;
	data->img = malloc(sizeof(t_img *) * 8);
	if (!data->img)
		return ;
	while (i <= 7)
	{
		data->img[i] = malloc(sizeof(t_img));
		if (!data->img[i])
			return ;
		i++;
	}
	data->sp = malloc(sizeof(t_sprite));
	if (!data->sp)
		return ;
	data->sp->buffer = malloc(sizeof(double) * (screenWidth + 1));
	if (!data->sp)
		return ;
	data->pl->totalrots = 0;
}

void	pl_init(t_data *data)
{
	data->pl->deX = 0;
	data->pl->deY = 0;
	data->pl->dirX = 0;
	data->pl->dirY = 0;
	data->pl->plX = 0;
	data->pl->plY = 0;
	data->pl->rot = 0;
	data->pl->totalrots = 0;
}
