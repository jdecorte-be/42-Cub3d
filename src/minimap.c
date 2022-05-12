#include "../inc/cub3d.h"

void    put_spawn(float x, float y)
{
    
}

void	trace_line(float x0, float y0, float x1, float y1,t_img *img)
{
    x0 *= 20;
    x1 *= 20;
    y1 *= 20;
    y0 *= 20;


	float x_step = x1 - x0;
	float y_step = y1 - y0;
	int max = find_max(find_mod(x_step), find_mod(y_step));
	x_step /= max;
	y_step /= max;
	while((int)(x0 - x1) || (int)(y0 - y1))
	{
        if (x0 < 1000 && y0 < 800 && x0 > 0 && y0 > 0)
            put_pxl(img, x0, y0, 0xffffff);
		x0 += x_step;
		y0 += y_step;
	}
}

void	tracing(int **tab, int height, int width, t_img *img)
{
	int i = 0;
	int j;

	while(i < height)
	{
		j = 0;
		while(j < width)
		{
			if (j < width - 1)
				trace_line(j, i, j + 1, i, img);
			if (i < height - 1)
				trace_line(j, i, j , i  + 1, img);
			j++;
		}
		i++;
	}
}