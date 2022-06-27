/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:27:25 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/27 13:57:42 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	isspawn(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	inmap(char c)
{
	if (c == '0' || isspawn(c))
		return (1);
	return (0);
}

int	ismap(char c)
{
	if (c == '1' || isspawn(c) || inmap(c))
		return (1);
	return (0);
}
