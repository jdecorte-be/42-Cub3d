/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:27:25 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/27 14:20:35 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

int	isspawn(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	isdoor(char c)
{
	if (c == 'D')
		return (1);
	return (0);
}

int	isitem(char c)
{
	if (c == '2')
		return (1);
	return (0);
}

int	inmap(char c)
{
	if (c == '0' || isspawn(c) || isitem(c) || isdoor(c))
		return (1);
	return (0);
}

int	ismap(char c)
{
	if (c == '1' || isspawn(c) || inmap(c))
		return (1);
	return (0);
}
