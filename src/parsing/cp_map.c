/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:27:47 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/23 13:09:57 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	take_map(t_file *file, t_map *map, char **tab)
{
	size_t	i;
	size_t	i2;

	if (!file->map_start)
		exit (write_error("Error\nMap error\n"));
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
			exit (write_error("Error\nMalloc failed\n"));
		i++;
	}
	map->map[i2] = 0;
	map->map_len = file->tab_len;
	return (0);
}
