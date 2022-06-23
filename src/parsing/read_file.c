/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:27:28 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/23 15:35:43 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	read_file(char **str, int fd)
{
	long		len;
	static int	i = 0;

	len = read(fd, *str, 10240);
	if (len == -1)
		return (1);
	(*str)[len] = 0;
	return (0);
}

int	get_file(int fd, char ***tab)
{
	char	*s1;
	char	*str;

	s1 = malloc(10241);
	str = 0;
	if (read_file(&s1, fd))
		exit (write_error("Error\nRead failed\n"));
	while (s1 && *s1)
	{
		if (are_printable(s1))
			exit (write_error("Error\nBad elem\n"));
		str = ft_free_join(str, s1, 1);
		if (!str || read_file(&s1, fd))
		{
			return (write_error("Error\nRead failed\n"));
		}
	}
	*tab = split1(str, '\n');
	if (!tab)
		return (write_error("Error\nMap empty\n"));
	free(s1);
	free(str);
	return (0);
}
