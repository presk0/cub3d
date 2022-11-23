/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:21:34 by supersko          #+#    #+#             */
/*   Updated: 2022/11/23 11:51:50 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_player *player, int move)
{
	double	radian_angle;

	radian_angle = (double)DEFAULT_ROTATION_ANGLE;
	if (move == LEFT)
		radian_angle *= -0.001;
	else if (move == RIGHT)
		radian_angle *= 0.001;
	// else if (move != RIGHT)
	// 	error_msg("[rotate_player] wrong instruction");
	rotate_vector(&player->direction, radian_angle);
}
