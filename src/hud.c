#include "../inc/cub3d.h"

void put_hud(t_data *data)
{
    int h;
    int w;
    
    // void *image = mlx_new_image(data->mlx, 200, 200);
    void *heal4 = mlx_xpm_file_to_image(data->mlx, "./res/heal4.xpm", &h, &w);
    void *sword = mlx_xpm_file_to_image(data->mlx, "./res/k_f0.xpm", &h, &w);
    // init_texture(data, 7, "./res/d_wall5.xpm");
    // mlx_put_image_to_window(data->mlx, data->mlx_win, sword, 300, screenHeight - 200);
    // mlx_put_image_to_window(data->mlx, data->mlx_win, heal4, 300, screenHeight - 120);
    int bt, s_line, endian;
    char *p_img = mlx_get_data_addr(heal4,&bt, &s_line, &endian);
    int i = 0;
    int px;
    while(i < 100)
    {
		px = (i * bt / 8) + (10 * s_line);

        data->img[0]->p_img[px] = p_img[px];
        data->img[0]->p_img[++px] = p_img[++px];
        data->img[0]->p_img[++px] = p_img[++px];
        
        i++;
    }
}