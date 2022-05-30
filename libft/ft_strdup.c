/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 09:59:21 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/05/25 23:21:14 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*s2;

	if (!s1)
		return (0);
	size = ft_strlen(s1);
	s2 = malloc(sizeof(*s2) * size + 1);
	if (!s2)
		ft_error(0, 2);
	ft_strlcpy(s2, s1, size + 1);
	return (s2);
}	
