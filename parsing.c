#include "parsing.h"

int	read_map(char **str, int fd)
{
	long	len;
	static int	i = 0;

	// printf("%d\n", i++);
	len = read(fd, *str, 10240);
	if (len == -1)
		return (1);
	(*str)[len] = 0;
	return (0);
}

int	are_printable(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isspace(str[i]) && (str[i] < 32 || str[i] > 126))
		{
			return (1);
		}
	}
	return (0);
}

int	are_space(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		if (!ft_isspace(str[i++]))
			return (0);
	return (1);
}

char	**ws_cute(char **tab)
{
	size_t	i;
	size_t	i2;
	char	*tmp;
	char	**ret;

	i = 0;
	i2 = 0;
	while (tab[i])
	{
		if (are_space(tab[i]))
			i2--;
		i++;
	}
	i2 += i;
	ret = malloc(sizeof(char *) * (i2 + 1));
	i2 = 0;
	i = 0;
	while (tab[i])
	{
		if (are_space(tab[i]) && i++)
			continue ;
		ret[i2] = tab[i++];
		i2++;
	}
	ret[i2] = 0;
	return (ret);
}

int	get_map(int fd, char ***tab)
{
	char	*s1;
	char	*str;

	s1 = malloc(10241);
	str = 0;
	if (read_map(&s1, fd))
		return (1);//
	while (s1 && *s1)
	{
		if (are_printable(s1))
			ft_error(0, 9);
		str = ft_free_join(str, s1, 1);
		if (read_map(&s1, fd))
			return (1);//
	}
	*tab = ws_cute(ft_split(str, "\n"));
	// for(int i=0;(*tab)[i];i++)
	// 	printf("%s\n", (*tab)[i]);
	free(s1);
	free(str);
	return (0);
}

// int	map_elem(t_map *map, char **tab)
// {
// 	size_t	i;
// 	size_t	i2;

// 	i = 0;
// 	i2 = 0;

// }

int	parse_map(t_map *map, char **argv)
{
	char	**tab;
	int		fd;
	
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	if (get_map(fd, &tab))
		return (1);
	close(fd);
	// if (map_elem(map, tab))
	// 	return (1);
	for(int i=0; tab[i]; i++)
		printf("%s\n", tab[i]);
	return (0);
	
}

int	parsing(t_map *map, char **argv)
{
	parse_map(map, argv);
	return (0);
}
