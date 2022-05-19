#ifndef PARSING_H
# define PARSING_H

# include "./libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_item
{
	char	type;
	size_t	px;
	size_t	py;
}	t_item;


typedef struct s_map
{
	char	*SO;
	char	*NO;
	char	*WE;
	char	*EA;
	char	*F;
	char	*C;
	char	**map;
	t_item	chart;
	t_item	*item;
}	t_map;


int		parsing(t_map *map, char **argv);
void	ft_error(void *arg, int e);
char	*ft_free_join(char const *s1, char const *s2, int e);

#endif