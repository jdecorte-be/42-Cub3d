/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:27:31 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/23 13:09:57 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	elem_type(char *str, size_t i)
{
	if (!ft_strncmp("NO ", &str[i], 2))
		return (1);
	else if (!ft_strncmp("SO ", &str[i], 2))
		return (2);
	else if (!ft_strncmp("WE ", &str[i], 2))
		return (3);
	else if (!ft_strncmp("EA ", &str[i], 2))
		return (4);
	else if (!ft_strncmp("F ", &str[i], 1))
		return (5);
	else if (!ft_strncmp("C ", &str[i], 1))
		return (6);
	else if (ismap(str[i]))
		return (7);
	else
		return (0);
}

void	cpl_free(t_file *file, int face)
{
	if (face == 1)
		free(file->no);
	else if (face == 2)
		free(file->so);
	else if (face == 3)
		free(file->we);
	else if (face == 4)
		free(file->ea);
	else if (face == 5)
		free(file->f);
	else if (face == 6)
		free(file->c);
}

int	cpl_face(t_file *file, char *str, size_t start, int face)
{
	size_t	end;

	end = start;
	while (str[end] && str[end] != 32)
		end++;
	if (face == 1 && ++file->f1)
		file->no = ft_substr(str, start, end - start);
	else if (face == 2 && ++file->f2)
		file->so = ft_substr(str, start, end - start);
	else if (face == 3 && ++file->f3)
		file->we = ft_substr(str, start, end - start);
	else if (face == 4 && ++file->f4)
		file->ea = ft_substr(str, start, end - start);
	else if (face == 5 && ++file->f5)
		file->f = ft_substr(str, start, end - start);
	else if (face == 6 && ++file->f6)
		file->c = ft_substr(str, start, end - start);
	if ((face == 1 && !file->no) || (face == 2 && !file->so)
		|| (face == 3 && !file->we) || (face == 4 && !file->ea)
		|| (face == 5 && !file->f) || (face == 6 && !file->c))
		ft_error(file, 2);
	return (0);
}

int	map_face(t_file *file, char *str, size_t i)
{
	int		face;

	i = 0;
	while (str[i] && (str[i] == 32 || str[i] == '\n'))
		i++;
	if (!str[i])
		return (0);
	face = elem_type(str, i);
	if (face == 0)
		exit (write_error("Error\nBad elem\n"));
	else if (face == 7)
		return (2);
	while (str[i] && str[i] != 32)
		i++;
	while (str[i] && str[i] == 32)
		i++;
	if (cpl_face(file, str, i, face))
		return (1);
	while (str[i] && str[i] != 32)
		i++;
	while (str[i] && str[i] == 32)
		i++;
	if (str[i])
		exit (write_error("Error\nBad elem\n"));
	return (0);
}

int	map_elem(t_file *file, char **tab)
{
	size_t	i;
	size_t	i2;
	size_t	i3;
	int		ret;

	i = 0;
	while (tab[i])
	{
		ret = map_face(file, tab[i], i3);
		if (ret == 1)
			return (1);
		else if (ret == 2)
		{
			file->map_start = i;
			return (0);
		}
		i++;
	}
	return (0);
}
