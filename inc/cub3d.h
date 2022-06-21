#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <time.h>
# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define screenWidth 900
# define screenHeight 680
# define CPL_ROT 2 * M_PI
# define ROTX CPL_ROT / 2880

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

typedef struct s_item
{
	char	type;
	int		px;
	int		py;
}	t_item;

typedef struct s_file
{
	int		f1;
	int		f2;
	int		f3;
	int		f4;
	int		f5;
	int		f6;
	char	*SO;
	char	*NO;
	char	*WE;
	char	*EA;
	char	*F;
	char	*C;
	size_t	map_start;
	size_t	tab_len;
}	t_file;

typedef struct l_sprite
{
	int texX;
	int texY;
	int stripe;
	double *buffer;
	double	invDet;
	double	transfX;
	double	transfY;
	int		vmovescreen;
	int		spriteScreenX;
	int spriteHeight;
	int drawStartY;
	int drawEndY;
	int spriteWidth;
	int drawStartX;
	int drawEndX;

}	t_sprite;

typedef struct l_time
{
	clock_t start;
	int n_frame;
	int tmp;
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
	double totalrots;
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
	size_t	map_len;
	char	**map;

	void	*NO;
	void	*SO;
	void	*WE;
	void	*EA;

	int		F;
	int		C;
	t_dlist	*spawn;
	t_list	*item;

	char dirSpawn;

}   t_map;

typedef struct l_data
{
	void *mlx;
	void *mlx_win;
	int n_taken;
	int n_sprites;
	t_sprite *sp;
	t_time	*t;
	t_img	**img;
	t_map *map;
	t_player *pl;
	t_dda *dda;
}   t_data;


void	draw_bg(t_data *data);
int	splitlen(char **tab);
void	update_param(t_data *data, double rot);
int	mousing(t_data *data);
void	ft_error(void *arg, int e);
void	set_spawn(t_data *data);
int	mousing(t_data *data);
void	check_dist(t_data *ptr);
void	calc_dda(t_data *ptr);
void	check_side(t_data *ptr);
void draw_verttext(t_data *data, int x, int y, t_img *text);
void draw_door(t_data *data, int x, int y);
void    update_fps(t_data *data);
void		set_plane(t_data *ptr, char flag);
void    init_data(t_data *data);
void put_spirtes(t_data *data);
void			run_draw(t_data *data);
int    key_handler(int key, t_data *data);
void			init_texture(t_data *ptr, int flag, char *path);
void	ft_free_tab(char **tab);
int	find_max(int num1, int num2);
int	find_mod(int num);
void    raycaster(t_data *data);
int mouse_hook(int key, t_data *data);
void	trace_line(float x0, float y0, float x1, float y1, t_img *img, int color);
char	*ft_free_join(char const *s1, char const *s2, int e);
void	put_pxl(t_img *img, int x, int y, int color);
void    put_spawn(t_data *data);
int		key_exit(int key, t_data *data);
void	minimap(t_data *data);
void    count_sprites(t_data *data);
void 	draw_sprites(t_data *data, double x, double y);
void	draw_door(t_data *data, int x, int y);
void	put_sprite(t_data *data, int y);

int		parsing(t_data *data, t_map *map, char **argv);
void	ft_error(void *arg, int e);
char	*ft_free_join(char const *s1, char const *s2, int e);
int		ft_atoi_positive(const char *str);

void 	put_hud(t_data *data);
t_dlist	*dlstnew(void *content);
void	dlstadd_back(t_dlist **lst, t_dlist *new);
void	dlst_free(t_dlist **lst);
void    find_spawn(char **map, t_data *data);
char	**split1(char const *s, char c);
int		free_tab(char **tab, int ret);

void    set_spawn(t_data *data);
void	pl_init(t_data *data);
void	struct_init(t_file *file, t_map *map);


int		write_error(char *str);
int		isspawn(char c);
int		isdoor(char c);
int		isitem(char c);
int		inmap(char c);
int		ismap(char c);

int		write_error(char *str);
int		are_printable(char *str);
int		are_space(char *str);
int		ft_free(void *a1, void *a2, void *a3, void *a4);
void	ft_tab_len(t_file *file, char **tab);

int		get_file(int fd, char ***tab);
int		map_elem(t_file *file, char **tab);
int		take_map(t_file *file, t_map *map, char **tab);
int		check_map(t_map *map);
int		conv_color(int *color, char *str);


#endif // !CUB3D_H