/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:27:47 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/22 16:36:11 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	take_map(t_file *file, t_map *map, char **tab)
{
	size_t	i;
	size_t	i2;

	if (!file->map_start)
		return (write_error("Error\nMap error\n"));
	ft_tab_len(file, tab);
	map->map = malloc(sizeof(char *) * (file->tab_len + 1));
	if (!map->map)
		ft_error(0, 2);
	i = file->map_start;
	i2 = 0;
	while (tab[i])
	{
		map->map[i2] = ft_strdup(tab[i]);
		if (!map->map[i2++])
			return (write_error("Error\nMalloc failed\n"));
		i++;
	}
	map->map[i2] = 0;
	map->map_len = file->tab_len;
	return (0);
}
