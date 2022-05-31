#include "../inc/cub3d.h"

void put_hud(t_data *data)
{
    int h;
    int w;
    void *sword = mlx_xpm_file_to_image(data->mlx, "./res/sword.xpm", &h, &w);
    // init_texture(data, 7, "./res/d_wall5.xpm");
    // mlx_put_image_to_window(data->mlx, data->mlx_win, sword, 300, 300);
}