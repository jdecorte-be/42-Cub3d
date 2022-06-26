/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:31:57 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/06/26 11:29:44 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_init_data(t_data *data)
{
	int	i;

	i = -1;
	free(data->pl);
	free(data->dda);
	free(data->t);
	free(data->sp->buffer);
	free(data->sp);
	while (++i <= 16)
		free(data->img[i]);
	free(data->img);
	free(data);
}

int	free_exit(t_data *data)
{
	int		i;
	t_list	*tmp;
	t_list	*tmp2;

	mlx_destroy_window(data->mlx, data->mlx_win);
	tmp = data->map->item;
	while (tmp)
	{
		tmp2 = tmp;
		free(tmp->content);
		tmp = tmp->next;
		free(tmp2);
	}
	i = -1;
	if (data->map && data->map->map)
		while (data->map->map[++i])
			free(data->map->map[i]);
	free(data->map->map);
	dlst_free(&data->map->spawn);
	free_init_data(data);
	exit(0);
}
