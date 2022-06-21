/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 22:44:43 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/21 09:39:49 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
