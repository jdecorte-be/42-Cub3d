#ifndef PARSING_H
# define PARSING_H

# include "./libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

typedef struct s_item
{
	char	type;
	size_t	px;
	size_t	py;
}	t_item;

typedef struct s_file
{
	int		f1;
	int		f2;
	int		f3;
	int		f4;
	int		f5;
	int		f6;
	char	*SO;
	char	*NO;
	char	*WE;
	char	*EA;
	char	*F;
	char	*C;
	size_t	map_start;
	size_t	tab_len;
}	t_file;

typedef struct s_map
{
	size_t	map_len;
	char	**tab;
	void	*SO;
	void	*NO;
	void	*WE;
	void	*EA;
	int		F;
	int		C;
	t_dlist	*spawn;
	t_list	*item;
}	t_map;


int		parsing(t_map *map, char **argv);
void	ft_error(void *arg, int e);
char	*ft_free_join(char const *s1, char const *s2, int e);
int		ft_atoi_positive(const char *str);


t_dlist	*dlstnew(void *content);
void	dlstadd_back(t_dlist **lst, t_dlist *new);
void	dlst_free(t_dlist **lst);

char	**split1(char const *s, char c);
int		free_tab(char **tab, int ret);
#endif