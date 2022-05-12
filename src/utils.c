#include "../inc/cub3d.h"

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	find_max(int num1, int num2)
{
	if (num1 > num2)
		return (num1);
	else
		return (num2);
}

int	find_mod(int num)
{
	if (0 > num)
		return (-num);
	return (num);
}

void	put_pxl(t_img *img, int x, int y, int color)
{
	int		i;

	i = (x * img->bt / 8) + (y * img->s_line);
    img->p_img[i] = color;
	img->p_img[++i] = color >> 8;
	img->p_img[++i] = color >> 16;
}
