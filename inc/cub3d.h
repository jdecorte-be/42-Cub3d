#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct l_img
{
	char    *p_img;
	int     bt;
	int		s_line;
	int		endian;
}   t_img;

typedef struct l_data
{
	void *mlx;
	void *mlx_win;
	int  height;
	int  width;
	t_img	img;
	t_img	point;
}   t_data;

int **parse_map(int mapWidth, int mapHeight);

void	ft_free_tab(char **tab);
int	find_max(int num1, int num2);
int	find_mod(int num);

void	trace_line(float x0, float y0, float x1, float y1, t_img *img);
void	put_pxl(t_img *img, int x, int y, int color);
void	tracing(int **tab, int height, int width, t_img *img);
void    put_spawn(float x, float y, t_img *img);

#endif // !CUB3D_H