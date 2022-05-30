/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:27:02 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/05/27 02:06:00 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nins(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (0);
	else
		return (1);
}

void	free_all(char *s1, char *s2, char **s3, char **s4)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	if (s3)
	{
		free(*s3);
		*s3 = NULL;
	}
	if (s4)
	{
		free(*s4);
		*s4 = NULL;
	}
}

void	third_gnl(char **backup, char **res)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while ((*backup)[i] && (*backup)[i] != '\n')
		i++;
	if ((*backup)[i] == '\n')
		i++;
	*res = ft_substr(*backup, 0, i);
	if (!*res)
	{
		free_all(NULL, NULL, NULL, backup);
		return ;
	}
	tmp = *backup;
	*backup = ft_strdup(tmp + i);
	if (!*backup || !**backup)
	{
		free_all(tmp, NULL, NULL, backup);
		return ;
	}
	free(tmp);
}

int	second_gnl(char **res, char *buff, char **backup, int fd)
{
	ssize_t	ret;
	char	*tmp;

	ret = 1;
	while (ret && ft_nins(*backup))
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
			return (1);
		buff[ret] = '\0';
		tmp = *backup;
		*backup = ft_strjoin(tmp, buff);
		free_all(tmp, NULL, NULL, NULL);
	}
	free_all(buff, NULL, NULL, NULL);
	third_gnl(backup, res);
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*backup;
	char		*res;

	res = 0;
	if (BUFFER_SIZE < 1 || fd < 0 || fd > OPEN_MAX)
		return (0);
	if (!backup)
		backup = ft_strdup("");
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	if (second_gnl(&res, buff, &backup, fd))
	{
		free_all(NULL, buff, 0, &backup);
		return (0);
	}
	if (res && *res == '\0')
		free_all(0, 0, &backup, &res);
	return (res);
}