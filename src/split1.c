/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:51:31 by jdecorte          #+#    #+#             */
/*   Updated: 2022/06/22 21:26:27 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	ft_count_words(const char *str, char c)
{
	int	count;
	int	i;
	int	trigger;

	i = 0;
	trigger = 1;
	count = 0;
	while (str[i])
	{
		if (str[i] == c && trigger == 0)
			trigger = 1;
		else if (str[i] == c && trigger == 1)
			count++;
		else if (str[i] != c && trigger == 1)
		{
			count++;
			trigger = 0;
		}
		i++;
	}
	return (count);
}

void	init(int *i, int *count, int *start, int *trig)
{
	*i = 0;
	*count = 0;
	*start = 0;
	*trig = 0;
}

static void	creat2(const char *s, char c, int *i, int *trig)
{
	if (s[*i] == c)
		(*i)++;
	else if (s[*i] && s[*i] != c)
	{
		while (s[*i] && s[*i] != c)
			(*i)++;
		*trig = 0;
	}
}

static char	**ft_to_create_tab(char **tab, const char *s, char c)
{
	int		count;
	int		i;
	int		start;
	int		trig;

	init(&count, &i, &start, &trig);
	while (s[i])
	{
		if (s[i] == c && trig == 0 && ++trig)
			start = ++i;
		else if (s[i] && (trig || s[i] != c))
		{
			creat2(s, c, &i, &trig);
			tab[count] = ft_substr(s, start, i - start);
			if (!tab[count++])
			{
				free_tab(tab, 0);
				return (0);
			}
			start = i;
		}
	}
	tab[count] = NULL;
	return (tab);
}

char	**split1(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (0);
	tab = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	return (ft_to_create_tab(tab, s, c));
}
