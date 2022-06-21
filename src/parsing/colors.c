/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:54:04 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/21 10:54:04 by jdecorte42       ###   ########.fr       */
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

int	conv_color(int *color, char *str)
{
	unsigned int	rgb[3];
	size_t			i;
	char			**tab;

	if (check_color_str(str))
		return (1);
	tab = ft_split(str, ",");
	if (tab == 0)
		return (write_error("Error\nmalloc_failed\n"));
	i = 0;
	while (tab[i] && i <= 4)
	{
		rgb[i] = ft_atoi_positive(tab[i]);
		i++;
	}
	if (i > 3)
		return (write_error("Error\nUse r,g,b format!\n"));
	i = 0;
	*color = 0;
	while (i < 3)
		if (ft_rgb(color, rgb, i++))
			return (1);
	return (0);
}
