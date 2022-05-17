#include "../inc/cub3d.h"

void			put_sprite(t_data *data, int y)
{
    int i;
    int j;

    j = data->img[5]->s_line * data->sp->texY + data->sp->texX * data->img[5]->bt / 8;
    if(data->img[5]->p_img[j] == 0 && data->img[5]->p_img[j + 1] == 0 && data->img[5]->p_img[j + 2] == 0)
        return ;
    i = data->sp->stripe * data->img[0]->bt / 8 + data->img[0]->s_line * y;
	data->img[0]->p_img[i] = data->img[5]->p_img[j];
	data->img[0]->p_img[++i] = data->img[5]->p_img[++j];
	data->img[0]->p_img[++i] = data->img[5]->p_img[++j];
}

int    count_sprites(char **map)
{
    int count = 0;
    int i = 0;
    int j;

    
    while(map[i])
    {
        while(map[i][j])
        {
            if(map[i][j] == '2')
                count++;
            j++;
        }
        i++;
    }
    return count;
}

void init_sprites(t_data *data)
{
    int i = 0;
    while(i < data->n_sprites)
    {

        i++;
    }
}

void draw_sprites(t_data *data, int x, int y)
{

	// int dist;
    // dist = pow(x - data->pl->posX, 2) + pow(y - data->pl->posY, 2);

    init_sprites(data);

    double invDet = 1.0 / (data->pl->plX * data->pl->dirY - data->pl->dirX * data->pl->plY);


    double transfX = (1.0 / (data->pl->plX * data->pl->dirY - data->pl->dirX * data->pl->plY)) * (data->pl->dirY * (x - data->pl->posX) - data->pl->dirX * (y - data->pl->posY));
    double transfY = (1.0 / (data->pl->plX * data->pl->dirY - data->pl->dirX * data->pl->plY)) * (-data->pl->plY * (x - data->pl->posX) + data->pl->plX * (y - data->pl->posY));

    int vmovescreen = 120 / transfY;

    int spriteScreenX = (int)((screenWidth / 2) * (1 + transfX / transfY));

    int spriteHeight = abs((int)(screenHeight / (transfY))) / 3;

    int drawStartY = -spriteHeight / 2 + screenHeight / 2 + vmovescreen;
    if(drawStartY < 0)
        drawStartY = 0;
    int drawEndY = spriteHeight / 2 + screenHeight / 2 + vmovescreen;
    if(drawEndY >= screenHeight)
        drawEndY = screenHeight - 1;

    int spriteWidth = abs((int)(screenHeight / (transfY))) / 3;

    int drawStartX = -spriteWidth / 2 + spriteScreenX;
    if(drawStartX < 0)
        drawStartX = 0;
    int drawEndX = spriteWidth / 2 + spriteScreenX;
    if(drawEndX >= screenWidth)
        drawEndX = screenWidth - 1;
    data->sp->stripe = drawStartX;
    while(data->sp->stripe < drawEndX)
    {
        data->sp->texX = (int)(256 * (data->sp->stripe - (-spriteWidth / 2 + spriteScreenX)) * data->img[5]->width / spriteWidth) / 256;
        if(transfY > 0 && data->sp->stripe > 0 && data->sp->stripe < screenWidth && transfY < data->sp->buffer[data->sp->stripe])
        {
            int y = drawStartY;
            while(y < drawEndY)
            {
                int d = (y - vmovescreen) * 256 - screenHeight * 128 + spriteHeight * 128;
                data->sp->texY = ((d * data->img[5]->height) / spriteHeight) / 256;
                put_sprite(data, y);
                y++;
            }
        }
        data->sp->stripe++;
    }
}
