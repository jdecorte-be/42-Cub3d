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

#define screenWidth 900
#define screenHeight 680

typedef struct l_sprite
{
	int texX;
	int texY;
	int stripe;
	double *buffer;

}	t_sprite;

typedef struct l_time
{
	double time;
	double oldtime;
	double ms;
	double rotspeed;
}	t_time;

typedef struct l_player
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double plX;
	double plY;
	double rot;
	double deX;
	double deY;
}   t_player;

typedef struct l_dda
{
	double		cam_x;
	int			screenx;
	double		raydir_x;
	double		raydir_y;
	int			map_x;
	int			map_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	double		walldist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	double		wallx;
	int			textx;
	int			texty;
	double		step;
	double		textpos;
}   t_dda;

typedef struct l_img
{
	char    *p_img;
	int			width;
	int			height;
	int     bt;
	int		s_line;
	int		endian;
}   t_img;

typedef struct l_map
{
	char	**map;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;

	char	*F;
	char	*T;

	char dirSpawn;

}   t_map;

typedef struct l_data
{
	void *mlx;
	void *mlx_win;
	int n_sprites;


	t_sprite *sp;
	t_time	*t;
	t_img	**img;
	t_map *map;
	t_player *pl;
	t_dda *dda;
}   t_data;

void    update_fps(t_data *data);
void		set_plane(t_data *ptr, char flag);
void    init_data(t_data *data);
void			run_draw(t_data *data);
char **parse_map(t_data *data, int fd);
int    key_handler(int key, t_data *data);
void			init_texture(t_data *ptr, int flag, char *path);
void	ft_free_tab(char **tab);
int	find_max(int num1, int num2);
int	find_mod(int num);
void    raycaster(t_data *data);
int mouse_hook(int key, t_data *data);
void	trace_line(float x0, float y0, float x1, float y1, t_img *img, int color);
void	put_pxl(t_img *img, int x, int y, int color);
void    put_spawn(t_data *data);
int    key_exit(int key, t_data *data);
void	minimap(t_data *data);
int    count_sprites(char **map);
void draw_sprites(t_data *data, int x, int y);
void draw_door(t_data *data, int x, int y);
void			put_sprite(t_data *data, int y);


#endif // !CUB3D_H