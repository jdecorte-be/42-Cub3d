/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_map_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:27:47 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/27 14:14:36 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static int	special_free(t_file *file, t_map *map)
{
	(void)map;
	ft_free(file->no, file->so, file->we, file->ea);
	ft_free(file->c, file->f, file, 0);
	return (write_error("Error\nMalloc failed\n"));
}

int	take_map(t_file *file, t_map *map, char **tab)
{
	size_t	i;
	size_t	i2;

	if (!file->map_start)
		exit (write_error("Error\nMap error\n"));
	ft_tab_len(file, tab);
	map->map = malloc(sizeof(char *) * (file->tab_len + 1));
	if (!map->map)
		return (special_free(file, map));
	i = file->map_start;
	i2 = 0;
	while (tab[i])
	{
		map->map[i2] = ft_strdup(tab[i]);
		if (!map->map[i2++])
			return (special_free(file, map));
		i++;
	}
	map->map[i2] = 0;
	map->map_len = file->tab_len;
	return (0);
}
