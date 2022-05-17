#include "../inc/cub3d.h"

void			put_door(t_data *data, int y)
{
    int i;
    int j;

    j = data->img[6]->s_line * data->sp->texY + data->sp->texX * data->img[6]->bt / 8;
    i = data->sp->stripe * data->img[0]->bt / 8 + data->img[0]->s_line * y;
	data->img[0]->p_img[i] = data->img[6]->p_img[j];
	data->img[0]->p_img[++i] = data->img[6]->p_img[++j];
	data->img[0]->p_img[++i] = data->img[6]->p_img[++j];
}

void draw_door(t_data *data, int x, int y)
{

	// int dist;

    // dist = pow(x - data->pl->posX, 2) + pow(y - data->pl->posY, 2);


    double invDet = 1.0 / (data->pl->plX * data->pl->dirY - data->pl->dirX * data->pl->plY);


    double transfX = (1.0 / (data->pl->plX * data->pl->dirY - data->pl->dirX * data->pl->plY)) * (data->pl->dirY * (x - data->pl->posX) - data->pl->dirX * (y - data->pl->posY));
    double transfY = (1.0 / (data->pl->plX * data->pl->dirY - data->pl->dirX * data->pl->plY)) * (-data->pl->plY * (x - data->pl->posX) + data->pl->plX * (y - data->pl->posY));


    int spriteScreenX = (int)((screenWidth / 2) * (1 + transfX / transfY));

    int spriteHeight = abs((int)(screenHeight / (transfY)));

    int drawStartY = -spriteHeight / 2 + screenHeight / 2;
    if(drawStartY < 0)
        drawStartY = 0;
    int drawEndY = spriteHeight / 2 + screenHeight / 2;
    if(drawEndY >= screenHeight)
        drawEndY = screenHeight - 1;

    int spriteWidth = abs((int)(screenHeight / (transfY)));

    int drawStartX = -spriteWidth / 2 + spriteScreenX;
    if(drawStartX < 0)
        drawStartX = 0;
    int drawEndX = spriteWidth / 2 + spriteScreenX;
    if(drawEndX >= screenWidth)
        drawEndX = screenWidth - 1;
    data->sp->stripe = drawStartX;
    while(data->sp->stripe < drawEndX)
    {
        data->sp->texX = (int)(256 * (data->sp->stripe - (-spriteWidth / 2 + spriteScreenX)) * data->img[6]->width / spriteWidth) / 256;
        if(transfY > 0 && data->sp->stripe > 0 && data->sp->stripe < screenWidth && transfY < data->sp->buffer[data->sp->stripe])
        {
            int y = drawStartY;
            while(y < drawEndY)
            {
                int d = y * 256 - screenHeight * 128 + spriteHeight * 128;
                data->sp->texY = ((d * data->img[6]->height) / spriteHeight) / 256;
                put_door(data, y);
                y++;
            }
        }
        data->sp->stripe++;
    }
}

