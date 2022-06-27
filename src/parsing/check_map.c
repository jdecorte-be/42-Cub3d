/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:40:11 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/27 13:42:47 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	add_item(t_map *map, int x, int y)
{
	t_item	*item;
	t_list	*tmp;
	t_dlist	*tmp2;

	item = malloc(sizeof(t_item));
	if (!item)
		return (1);
	item->type = map->map[y][x];
	item->px = x;
	item->py = y;
	if (isspawn(map->map[y][x]))
	{
		tmp2 = dlstnew(item);
		if (!tmp2)
			return (1);
		dlstadd_back(&map->spawn, tmp2);
	}
	else if (isitem(map->map[y][x]))
	{
		tmp = ft_lstnew(item);
		if (!tmp)
			return (1);
		ft_lstadd_back(&map->item, tmp);
	}
	return (0);
}

int	check(t_map *map, size_t *map_len)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (inmap(map->map[y][x]) && !(x && ismap(map->map[y][x - 1])
				&& map->map[y][x + 1] && ismap(map->map[y][x + 1])
				&& y && map_len[y - 1] >= x + 1 && ismap(map->map[y - 1][x - 1])
				&& ismap(map->map[y - 1][x]) && ismap(map->map[y - 1][x + 1])
				&& map->map[y + 1] && map_len[y + 1] >= x
				&& ismap(map->map[y + 1][x - 1])
				&& ismap(map->map[y + 1][x]) && ismap(map->map[y + 1][x + 1])))
				return (write_error("Error\nMap isnt close\n"));
			if (isspawn(map->map[y][x]) || isitem(map->map[y][x]))
				if (add_item(map, x, y))
					return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	cpl_map_len(char **map, size_t	**map_len)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!(ismap(map[y][x]) || map[y][x] == 32 || map[y][x] == '\n'))
				return (write_error("Error\nMap elem error\n"));
			x++;
		}
		(*map_len)[y] = x;
		y++;
	}
	return (0);
}

int	check_map(t_map *map)
{
	size_t	*map_len;

	map_len = malloc(sizeof(size_t) * map->map_len);
	if (!map_len)
		return (write_error("Error\nNeed map\n"));
	if (cpl_map_len(map->map, &map_len))
	{
		free(map_len);
		return (1);
	}
	if (check(map, map_len))
	{
		free(map_len);
		return (1);
	}
	if (!map->spawn)
	{
		free(map_len);
		return (write_error("Error\nNeed spawn\n"));
	}
	free(map_len);
	return (0);
}
