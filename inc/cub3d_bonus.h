/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:14:10 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/06/27 14:13:23 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "cub3d.h"

int		mousing(t_data *data);
int		isdoor(char c);
int		isitem(char c);
void	draw_bg(t_data *data);
void	minimap(t_data *data);
void	put_sprite(t_data *data, int y);

#endif