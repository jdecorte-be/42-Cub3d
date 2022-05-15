#include "../inc/cub3d.h"

void	trace_line(float x0, float y0, float x1, float y1,t_img *img, int color)
{
    x0 *= 10;
    x1 *= 10;
    y1 *= 10;
    y0 *= 10;


	float x_step = x1 - x0;
	float y_step = y1 - y0;
	int max = find_max(find_mod(x_step), find_mod(y_step));
	x_step /= max;
	y_step /= max;
	while((int)(x0 - x1) || (int)(y0 - y1))
	{
        if (x0 < 1000 && y0 < 800 && x0 > 0 && y0 > 0)
            put_pxl(img, x0, y0, color);
		x0 += x_step;
		y0 += y_step;
	}
}



void	draw_wall(t_data *data, double x, double y)
{
	double i = y;
	while(i < y + 1)
	{
		trace_line(x, i, x + 1, i, data->img[0], 0xffffff);
		i += 0.1; // a changer pour augmenter les fps
	}
}

int splitlen(char **tab)
{
	int i = 0;
	while(tab[i])
		i++;
	return i;
}

void	minimap(t_data *data)
{
	int i = 0;
	int j;
	int t_posX = 10.5;
	int t_posY = 10.5;
	// trace_line(1, 1, 20, 1, data->img[0], 0xffffff);
	// trace_line(1, 1, 1, 20, data->img[0], 0xffffff);
	// trace_line(20, 1, 20, 20, data->img[0], 0xffffff);
	// trace_line(1, 20, 20, 20, data->img[0], 0xffffff);

	trace_line(t_posX, t_posY, (t_posX + data->pl->dirX - data->pl->plX), (t_posY + data->pl->dirY - data->pl->plY),data->img[0], 0xf7948e);
	trace_line(t_posX, t_posY, (t_posX + data->pl->dirX + data->pl->plX), (t_posY + data->pl->dirY + data->pl->plY),data->img[0], 0xf7948e);

	int x = 0;
	int y = 0;
	while(data->map->map[x])
	{
		y = 0;
		while(data->map->map[x][y])
		{
			if(data->map->map[x][y] == '1')
				draw_wall(data, x + data->pl->posX , y + data->pl->posY);
			y++;
		}
		x++;
	}
}