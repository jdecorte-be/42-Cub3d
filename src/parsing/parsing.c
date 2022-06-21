/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:26:13 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/21 15:26:38 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	all_face(t_file *file)
{
	if (!file->f1)
		return (1);
	if (!file->f2)
		return (1);
	if (!file->f3)
		return (1);
	if (!file->f4)
		return (1);
	if (!file->f5)
		return (1);
	if (!file->f6)
		return (1);
	return (0);
}

int	parse_map(t_map *map, t_file *file, char **argv)
{
	char	**tab;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (write_error("Error\nOpen failed\n"));
	if (get_file(fd, &tab))
		return (1);
	close(fd);
	if (map_elem(file, tab))
		return (1);
	if (all_face(file))
		return (1);
	if (take_map(file, map, tab))
		return (1);
	if (check_map(map))
		return (1);
	return (0);
}

int	ext_cub(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (i && str[i] != '.')
		i--;
	if (!i || ft_strncmp(".cub", &str[i], 4))
		return (write_error("Error\nBad extension\n"));
	return (0);
}

int	convert_file(t_data *data, t_map *map, t_file *file)
{
	init_texture(data, 1, file->NO);
	init_texture(data, 2, file->SO);
	init_texture(data, 3, file->WE);
	init_texture(data, 4, file->EA);
	init_texture(data, 5, "./res/door1.xpm");
	init_texture(data, 6, "./res/frame_0.xpm");
	init_texture(data, 7, "./res/frame_1.xpm");
	init_texture(data, 8, "./res/frame_2.xpm");
	init_texture(data, 9, "./res/frame_3.xpm");
	init_texture(data, 10, "./res/frame_4.xpm");
	init_texture(data, 11, "./res/frame_5.xpm");
	init_texture(data, 12, "./res/frame_6.xpm");
	if (conv_color(&map->F, file->F) || conv_color(&map->C, file->C))
		return (write_error("Error\nColor error\n"));
	return (0);
}

int	parsing(t_data *data, t_map *map, char **argv)
{
	t_file	file;

	if (ext_cub(argv[1]))
		return (1);
	struct_init(&file, map);
	if (parse_map(map, &file, argv))
		return (1);
	if (convert_file(data, map, &file))
		return (1);
	return (0);
}
