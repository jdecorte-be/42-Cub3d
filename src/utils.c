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

	if(x < screenWidth && y < screenHeight)
	{
		i = (x * img->bt / 8) + (y * img->s_line);
		img->p_img[i] = color;
		img->p_img[++i] = color >> 8;
		img->p_img[++i] = color >> 16;
	}
}

static void	free_join(void *s1, void *s2, int e)
{
	if (e == 1 || e == 3)
		free(s1);
	else if (e == 2 || e == 3)
		free(s2);
}

char	*ft_free_join(char const *s1, char const *s2, int e)
{
	char	*dst;
	size_t	i;
	size_t	len_s1;
	size_t	len_dst;

	if (!s1)
		return (ft_strdup((char *)s2));
	if (!s2)
		return (ft_strdup((char *)s1));
	len_s1 = ft_strlen(s1);
	len_dst = len_s1 + ft_strlen(s2);
	dst = malloc(sizeof(*dst) * len_dst + 1);
	if (!dst)
		return (0);
	i = -1;
	while (s1[++i])
		dst[i] = s1[i];
	i = -1;
	while (s2[++i])
		dst[len_s1 + i] = s2[i];
	dst[len_s1 + i] = '\0';
	if (e)
		free_join((void *)s1, (void *)s2, e);
	return (dst);
}

int	ft_atoi_positive(const char *str)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	if (!str || !str[i])
		return (-1);
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		nb = nb * 10 + (str[i++] - 48);
		if (nb > 2147483647)
			return (-1);
	}
	if (str[i])
		return (-1);
	return (nb);
}

int	free_tab(char **tab, int ret)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (ret);		
}

void	struct_init(t_file *file, t_map *map)
{
	file->map_start = 0;
	file->tab_len = 0;
	file->NO = 0;
	file->SO = 0;
	file->WE = 0;
	file->EA = 0;
	file->F = 0;
	file->C = 0;
	file->f1 = 0;
	file->f2 = 0;
	file->f3 = 0;
	file->f4 = 0;
	file->f5 = 0;
	file->f6 = 0;
	map->spawn = 0;
	map->item = 0;
}
