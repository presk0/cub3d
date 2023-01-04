/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko        #+#    #+#             */
/*   Updated: 2023/01/04 18:39:23 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

void	player_smoth_move(t_data *data)
{
	direction_move(data);
}

int	move_player(t_data *data, int move)
{
	int			hit_wall;
	t_player	*p;
	t_vector	scaled_direction;

	p = data->player;
	if (data->player->speed == 1)
		scaled_direction = vec_scale(p->direction, \
			(double)(UNITS_PER_BOX / 15));
	else
		scaled_direction = vec_scale(p->direction, \
			(double)(UNITS_PER_BOX / STEPS_PER_BOX));
	if (move == BACKWARD)
		rotate_vector(&scaled_direction, degree_to_radian(180));
	else if (move == RIGHT)
		rotate_vector(&scaled_direction, degree_to_radian(90));
	else if (move == LEFT)
		rotate_vector(&scaled_direction, degree_to_radian(-90));
	translate_pt_inplace(scaled_direction, &p->pos_box);
	hit_wall = check_update_box_pos(data);
	update_pos_in_step(p);
	update_pos_in_pix(p);
	return (hit_wall);
}
