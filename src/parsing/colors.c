/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:54:04 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/24 19:06:27 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_color_str(char *str)
{
	size_t	i;
	size_t	com;

	i = 0;
	com = 0;
	while (str[i] && com <= 2)
	{
		if (str[i] == ',')
			com++;
		i++;
	}
	if (com > 2)
		return (1);
	return (0);
}

int	ft_rgb(int *color, unsigned int rgb[3], int i)
{
	if (rgb[i] > 255)
		return (1);
	*color += (rgb[i] << (((i + 2) - (i * 2)) * 8));
	return (0);
}

size_t	search(char *str, size_t start)
{
	size_t		end;
	size_t		check_point;
	static int	set;

	set = 2;
	end = start;
	while (str[end] && (!set || str[end] != ','))
	{
		if (str[end] == ',')
			set--;
		if (!ft_isspace(str[end]))
			check_point = ++end;
		else
			end++;
	}
	return (check_point);
}

char	**color_split(char *str)
{
	char	**tab;
	size_t	end;
	size_t	start;
	size_t	i;

	end = 0;
	start = 0;
	i = 0;
	tab = malloc(sizeof(char *) * 4);
	while (i < 3)
	{
		start = end;
		while (str[start] && str[start] == 32)
			start++;
		if (str[start] == ',')
			start++;
		while (str[start] && str[start] == 32)
			start++;
		end = search(str, start);
		tab[i] = ft_substr(str, start, end - start);
		if (!tab[i++] && free_tab(tab, 1))
			return (0);
	}
	tab[i] = 0;
	return (tab);
}

int	conv_color(int *color, char *str)
{
	unsigned int	rgb[3];
	size_t			i;
	char			**tab;

	if (check_color_str(str))
		return (1);
	tab = color_split(str);
	if (tab == 0)
		exit (write_error("Error\nmalloc_failed\n"));
	i = 0;
	while (tab[i])
	{
		rgb[i] = ft_atoi_positive(tab[i]);
		i++;
	}
	i = 0;
	*color = 0;
	while (i < 3)
		if (ft_rgb(color, rgb, i++))
			return (ft_free(tab[0], tab[1], tab[2], tab));
	ft_free(tab[0], tab[1], tab[2], tab);
	return (0);
}
