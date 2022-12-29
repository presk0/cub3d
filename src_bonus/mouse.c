/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 04:02:46 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/29 14:39:37 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	mouse_rotate(t_data *data)
{
	t_point		pos;
	t_point		delta;

	if (data->mouse == 0)
		return ;
	mlx_mouse_get_pos(data->window->mlx, data->window->init, &pos.x, &pos.y);
	delta.x = pos.x - data->window->width / 2;
	delta.y = pos.y - data->window->height / 2;
	if (delta.x < 0)
		rotate_player(data->player, LEFT);
	else if (delta.x > 0)
		rotate_player(data->player, RIGHT);
	mlx_mouse_move(data->window->mlx, data->window->init, \
	data->window->width / 2, data->window->height / 2);
}

int	mouse_event(t_data *data)
{
	data->mouse = 1;
	mlx_mouse_hide(data->window->mlx, data->window->init);
	return (0);
}