#include "parsing.h"

int isspawn(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	isitem(char c)
{
	if (c == 2) //|| c == 3 ...)
		return (1);
	return (0);
}

int	inmap(char c)
{
	if (c == '0' || isitem(c) || isspawn(c))
		return (1);
	return (0);
}

int	ismap(char c)
{
	if (c == '1' || isspawn(c) || inmap(c))
		return (1);
	return (0);
}

int	read_file(char **str, int fd)
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

int	ft_free(void *a1, void *a2, void *a3, void *a4)
{
	if (a1)
		free(a1);
	if (a2)
		free(a2);
	if (a3)
		free(a3);
	if (a4)	
		free(a4);
	return (1);
}

char	**ws_cute(char **tab)
{
	size_t	i;
	size_t	i2;
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
		if (are_space(tab[i]) && ft_free(tab[i++], 0, 0, 0))
			continue ;
		ret[i2] = tab[i++];
		i2++;
	}
	ret[i2] = 0;
	free(tab);
	return (ret);
}

int	get_file(int fd, char ***tab)
{
	char	*s1;
	char	*str;

	s1 = malloc(10241);
	str = 0;
	if (read_file(&s1, fd))
		return (1);//
	while (s1 && *s1)
	{
		if (are_printable(s1))
			ft_error(0, 9);
		str = ft_free_join(str, s1, 1);
		if (read_file(&s1, fd))
			return (1);//
	}
	*tab = split1(str, '\n');
	// for(int i=0;(*tab)[i];i++)
	// 	printf("%s\n", (*tab)[i]);
	free(s1);
	free(str);
	return (0);
}

int	elem_type(char *str, size_t i)
{
	// printf("str == %c\n", str[i]);
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
	{
		// printf("%d\n", i);
		return (0);
	}
}

void	cpl_free(t_file *file, int face)
{
	if (face == 1)
		free(file->NO);
	else if (face == 2)
		free(file->SO);
	else if (face == 3)
		free(file->WE);
	else if (face == 4)
		free(file->EA);
	else if (face == 5)
		free(file->F);
	else if (face == 6)
		free(file->C);
}

int	cpl_face(t_file *file, char *str, size_t start, int face)
{
	size_t	end;

	end = start;
	while (str[end] && str[end] != 32)
		end++;
	if (face == 1 && ++file->f1)
		file->NO = ft_substr(str, start, end - start);
	else if (face == 2 && ++file->f2)
		file->SO = ft_substr(str, start, end - start);
	else if (face == 3 && ++file->f3)
		file->WE = ft_substr(str, start, end - start);
	else if (face == 4 && ++file->f4)
		file->EA = ft_substr(str, start, end - start);
	else if (face == 5 && ++file->f5)
		file->F = ft_substr(str, start, end - start);
	else if (face == 6 && ++file->f6)
		file->C = ft_substr(str, start, end - start);
	if ((face == 1 && !file->NO) || (face == 2 && !file->SO)
		|| (face == 3 && !file->WE) || (face == 4 && !file->EA)
		|| (face == 5 && !file->F) || (face == 6 && !file->C))
		ft_error(file, 2);
	return (0);
}

int	map_face(t_file *file, char *str)
{
	size_t	i;
	int		face;

	i = 0;
	while (str[i] && (str[i] == 32 || str[i] == '\n'))
		i++;
	if (!str[i])
		return (0);
	face = elem_type(str, i);
	if (face == 0)
	{
		// printf("caca\n");
		return (1);
	}
	else if (face == 7)
	{
		return (2);
	}
	while (str[i] && str[i] != 32)
		i++;
	while (str[i] && str[i] == 32)
		i++;
	// printf("face == %d\n", face);
	if (cpl_face(file, str, i, face))
		return (1);
	while (str[i] && str[i] != 32)
		i++;
	while (str[i] && str[i] == 32)
		i++;
	if (str[i])
		return (1);
	return (0);
}

int	map_elem(t_file *file, char **tab)
{
	size_t	i;
	size_t	i2;
	int		ret;

	i = 0;
	while (tab[i])
	{
		// printf("zu %zu\n", i);
		ret = map_face(file, tab[i]);
		// printf("ret == %d\n", ret);
		if (ret == 1)
			return (1);
		else if (ret == 2)
		{
			file->map_start = i;
			return (0);
		}
		i++;
		// else if (ft_strncmp("F ", tab[i][i2], 2))
		// else if (ft_strncmp("C ", tab[i][i2], 2))
	}
	return (0);
}

void	ft_tab_len(t_file *file, char **tab)
{
	size_t	i;

	i = file->map_start;
	printf("%zu \n", i);
	while (tab[i])
		i++;
	// 	printf("%s\n", tab[i++]);
	// printf("%zu\n", i);
	file->tab_len = i - file->map_start;
}

int	take_map(t_file *file, t_map *map, char **tab)
{
	size_t	i;
	size_t	i2;
	// size_t	i3;

	ft_tab_len(file, tab);
	map->map = malloc(sizeof(char *) * (file->tab_len + 1));
	if (!map->map)
		ft_error(0, 2);
	i = file->map_start;
	// i3 = 0;
	i2 = 0;
	while (tab[i])
	{
		// i2 = 0;
		// while (tab[i][i2] && tab[i][i2] == 32)
		// 	i2++;
		// if (tab[i][i2] == '1')
		map->tab[i2++] = tab[i];
		i++;
	}
	map->tab[i2] = 0;
	// for (int z=0;map->tab[z];z++)
	// 	printf("%s\n", map->tab[z]);
	map->map_len = file->tab_len;
	return (0);
}

int	check(t_map *map, size_t *map_len)
{
	size_t	x;
	size_t	y;
	t_item	item;

	y = 0;
	while (map->tab[y])
	{
		x = 0;
		while (map->tab[y][x])
		{
			if (map->tab[y][x] == '\n' || (ismap(map->tab[y][x] && inmap(map->tab[y][x]) && !(x && ismap(map->tab[y][x - 1]) && map->tab[y][x + 1] && ismap(map->tab[y][x + 1]) && y && map_len[y - 1] >= x + 1 && ismap(map->tab[y - 1][x - 1]) && ismap(map->tab[y - 1][x]) && ismap(map->tab[y - 1][x + 1]) && map->tab[y + 1] && map_len[y + 1] >= x && ismap(map->tab[y + 1][x - 1]) && ismap(map->tab[y + 1][x]) && ismap(map->tab[y + 1][x + 1])))))
			{
				// printf("%zu %zu\n", x, y);
				// printf("error\n");
				return (1);
			}
			if (isspawn(map->tab[y][x]))
			{
				item.type = map->tab[y][x];
				item.px = x;
				item.py = y;
				dlstadd_back(&map->spawn, dlstnew(&item));
			}
			if (isitem(map->tab[y][x]))
			{
				item.type = map->tab[y][x];
				item.px = x;
				item.py = y;
				ft_lstadd_back(&map->item, ft_lstnew(&item));
			}
			x++;
		}
		// (*map_len)[y] = x - 1;
		y++;
			
	}
	return (0);
}

void	cpl_map_len(char **map, size_t	**map_len)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
			x++;
		(*map_len)[y] = x;
		y++;
	}
}

// int	h_check(char **map, size_t	*map_len)
// {
// 	size_t	x;
// 	size_t	y;

// 	y = 0;
// 	x = 0;
// 	while (map[y][x])
// 	{
// 		y = 0;
// 		while ()
// 	}
// }

int	check_map(t_map *map)
{
	size_t	*map_len;

	map_len = malloc(sizeof(size_t) * map->map_len);
	if (!map_len)
		ft_error(map, 2);
	cpl_map_len(map->tab, &map_len);
	if (check(map, map_len))
		return (1);
	if (!map->spawn)
	{
		write(2, "no spawn\n", 9);
		// printf("\n");
		return (1);
	}
	// printf("c == %d\n", map->spawn_dir.type);
	// if (v_check(map->tab), map_len)
	// 	return (1);
	return (0);
}

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
		return (1);
	if (get_file(fd, &tab))
		return (1);
	close(fd);
	// tab = ws_cute(tab);
	if (map_elem(file, tab))
		return (1);
	// printf("caca1\n");
	if (all_face(file))
		return (1);
	if (take_map(file, map, tab))
		return (1);
	if (check_map(map))
		return (1);
	printf("%s\n", file->NO);
	printf("%s\n", file->SO);
	printf("%s\n", file->WE);
	printf("%s\n", file->EA);
	printf("%s\n", file->F);
	printf("%s\n", file->C);
	printf("%zu\n", file->tab_len);
	return (0);
	
}

void	file_init(t_file *file)
{
	file->tab_len = 0;
	file->NO = 0;
	file->SO = 0;
	file->WE = 0;
	file->EA = 0;
	file->F = 0;
	file->C = 0;
	file->f1 = 0;
	file->f2 = 0;
	file->f3 = 0;
	file->f4 = 0;
	file->f5 = 0;
	file->f6 = 0;
}


// void	map_init(t_map *map)
// {
// 	map->spawn_dir.type = 0;
// 	map->spawn_dir.px = 0;
// 	map->spawn_dir.py = 0;
// 	map->item = 0;
// }

int	ext_cub(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (i && str[i] != '.')
		i--;
	// peut etre retire le !i en bas on sait pas pour le cas du fichier ".cub" si on l accept ou pas
	if (!i || ft_strncmp(".cub", &str[i], 4))
		return (1);
	return (0);
}

int	check_color_str(char *str)
{
	size_t	i;
	size_t	com;

	i = 0;
	com  = 0;
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

int	conv_color(int *color, char *str)
{
	unsigned int rgb[3];
	size_t	i;
	char **tab;


	if (check_color_str(str))
		return (1);
	tab = ft_split(str, ",");
	if (tab == 0)
	{
		// mallocfail
		return (1);
	}
	i = 0;
	while (tab[i] && i <= 4)
	{
		// printf("tab[%d] == %s\n", i, tab[i]);
		rgb[i] = ft_atoi_positive(tab[i]);
		// printf("rgb[%d] == %p\n", i, rgb[i]);
		i++;
	}
	if (i > 3)
	{
		write(2, "trop de couleur\n", 16);
		return (1);
	}
	i = 0;
	*color = 0;
	while (rgb[i] && i < 3)
	{
		if (rgb[i] > 255)
		{
			// write(2, "color value error\n", 18);
			return (1);
		}
		// printf("%p\n", rgb[i]);
		// printf("%d\n", (((i + 2) - (i * 2)) * 8));
		*color += (rgb[i] << (((i + 2) - (i * 2)) * 8));
		i++;
	}
	// printf("color == %p\n", *color);
	return (0);
}

int	convert_file(t_map *map, t_file *file)
{
	//ft (xpm to img)

	if (conv_color(&map->F, file->F) || conv_color(&map->C, file->C))
	{
		write(2, "color error\n", 12);
		return (1);
	}
	// printf("caca\n");
	// if (take_item())
	// printf("F == %p\n", map->F);
	// printf("c == %p\n", map->C);
	return (0);
}

int	parsing(t_map *map, char **argv)
{
	t_file	file;

	// map_init(map);
	if (ext_cub(argv[1]))
	{
		write(2, "Error\nextantion\n", 16);
		return (1);
	}
	file_init(&file);
	if (parse_map(map, &file, argv))
		write(2, "map error\n", 10);
	if (convert_file(map, &file))
		return (1);
	// for(int i=0; map->tab[i]; i++)
	// 	printf("%s\n", map->tab[i]);
	return (0);
}
// 