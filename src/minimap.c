#include "../inc/cub3d.h"

void	trace_line(float x0, float y0, float x1, float y1,t_img *img, int color)
{
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

void	trace_line_wall(float x0, float y0, float x1, float y1,t_img *img, int color)
{
	float x_step = x1 - x0;
	float y_step = y1 - y0;
	int max = find_max(find_mod(x_step), find_mod(y_step));
	x_step /= max;
	y_step /= max;
	while((int)(x0 - x1) || (int)(y0 - y1))
	{
        if (x0 < 200 && y0 < 200 && x0 > 0 && y0 > 0)
            put_pxl(img, x0, y0, color);
		x0 += x_step;
		y0 += y_step;
	}
}


void	draw_wall(t_data *data, double x, double y)
{
	double i = y;
	double t_y;
	double t_x;
	double t_x2;
	double t_y2;

	
	while(i < y + 15)
	{
		//printf("%f %f \n", x, y);
		// t_x = (x) * cos(data->pl->totalrots) - (i) * sin(data->pl->totalrots);
		// t_y = (x) * sin(data->pl->totalrots) + (i) * cos(data->pl->totalrots);
		// t_x2 = (x + 15) * cos(data->pl->totalrots) - (i) * sin(data->pl->totalrots);
		// t_y2 = (x + 15) * sin(data->pl->totalrots) + (i) * cos(data->pl->totalrots);
		
		trace_line_wall(x, i, x + 15,i ,data->img[0], 0xB85E4F); //printf("%f %f -> %f %f\n", t_x, t_y, t_x2, t_y);

		// trace_line_wall(t_x - 15 + 75, t_y + 100, t_x2 - 15 + 75, t_y2 + 100, data->img[0], 0xB85E4F); //printf("%f %f -> %f %f\n", t_x, t_y, t_x2, t_y);
		i += 0.3; // a changer pour augmenter les fps
	}
}

void	draw_spawn(t_data *data, double x, double y)
{
	double i = y;
	while(i < y + 10)
	{
		trace_line(x, i, x + 10, i, data->img[0], 0xDC143C);
		i += 1; // a changer pour augmenter les fps
	}
}

void	draw_bg(t_data *data)
{
	double i = 10;
	while(i < 200)
	{
		trace_line(10, i, 200, i, data->img[0], 0xE1D5C8);
		i += 1; // a changer pour augmenter les fps
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
	draw_bg(data);
	trace_line(10, 10, 200, 10, data->img[0], 0x4C3232);
	trace_line(10, 10, 10, 200, data->img[0], 0x4C3232);
	trace_line(200, 10, 200, 200, data->img[0], 0x4C3232);
	trace_line(10, 200, 200, 200, data->img[0], 0x4C3232);

	// trace_line_wall(100, 100, (data->pl->posX + data->pl->dirX - data->pl->plX) * 15 + 100, (data->pl->posY + data->pl->dirY - data->pl->plY) * 10 - 100,data->img[0], 0xf7948e);
	// trace_line_wall(100, 100, (data->pl->posX + data->pl->dirX + data->pl->plX) * 15 + 100, (data->pl->posY + data->pl->dirY + data->pl->plY) * 10 - 100,data->img[0], 0xf7948e);

	int x = 0;
	int y = 0;
	int x_len = splitlen(data->map->map);
	
	while(data->map->map[x])
	{
		y = 0;
		while(data->map->map[x][y])
		{
			if(data->map->map[x][y] == '1')
			{
				int xc = ((x) - data->pl->posY) * 15 + 150;
				int yc = (y + data->pl->posX) * 15;
				draw_wall(data,yc, xc);
				// draw_wall(data,(x_len - x) * 15 - 75, (y) * 15 - 100);
			}
			y++;
		}
		x++;
	}
	draw_spawn(data, 100, 100);
}