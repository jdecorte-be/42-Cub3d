#include "parsing.h"

void	ft_error(void *arg, int e)
{
	if (e == 2)
		write (2, "malloc\n", 7);
	else if (e == 9)
		write (2, "map error\n", 10);
	exit (1);
}

void	map_init(t_map *map)
{
	map->spawn = 0;
	map->item = 0;
}

int main(int argc, char **argv)
{
	t_map	map;

	map_init(&map);
	parsing(&map, argv);
}