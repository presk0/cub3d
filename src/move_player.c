/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko        #+#    #+#             */
/*   Updated: 2022/12/15 03:49:30 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* check if it steps out of a box */
int	f_is_box_crossed(t_player *player)
{
	int	direction;

	direction = 0;
	if (player->pos_box.y < 0)
		direction += N;
	if (player->pos_box.y >= UNITS_PER_BOX)
		direction += S;
	if (player->pos_box.x < 0)
		direction += E;
	if (player->pos_box.x >= UNITS_PER_BOX)
		direction += W;
	return (direction);
}

int	update_pos_if_wall(t_data *data, int crossover_direction)
{
	int		hit_wall;

	hit_wall = 0;
	if (crossover_direction == N || crossover_direction == NE \
		|| crossover_direction == NW)
		hit_wall += north_crossing(data);
	if (crossover_direction == S || crossover_direction == SE \
		|| crossover_direction == SW)
		hit_wall += south_crossing(data);
	if (crossover_direction == E || crossover_direction == SE \
		|| crossover_direction == NE)
		hit_wall += east_crossing(data);
	if (crossover_direction == W || crossover_direction == NW \
		|| crossover_direction == SW)
		hit_wall += west_crossing(data);
	if (!hit_wall)
	{
		if (crossover_direction == NE || crossover_direction == SW \
			|| crossover_direction == NW || crossover_direction == SE)
			hit_wall = corner_crossing(data);
	}
	fprintf(stderr, "update_pos_if_wall: hit_wall = %d\n", hit_wall);
	return (hit_wall);
}

/* return 1 if same, 2 if changed boxes, 0 if hit a wall) */
int	check_update_box_pos(t_data *data)
{
	int	has_cross_over;
	int	hit_wall;

	hit_wall = 0;
	has_cross_over = f_is_box_crossed(data->player);
	if (has_cross_over)
		hit_wall += update_pos_if_wall(data, has_cross_over);
	return (hit_wall);
}

void	direction_move(t_data *data)
{
	if (data->key_status->w == 1)
		move_player(data, FORWARD);
	if (data->key_status->s == 1)
		move_player(data, BACKWARD);
	if (data->key_status->a == 1)
		move_player(data, LEFT);
	if (data->key_status->d == 1)
		move_player(data, RIGHT);
	if (data->key_status->left == 1)
		rotate_player(data->player, LEFT);
	if (data->key_status->right == 1)
		rotate_player(data->player, RIGHT);
}

void	player_smoth_move(t_data *data)
{
	static int	counter;
	static int	counter2;

	if (data->player->speed == 1 && data->player->stamina > 0)
	{
		counter++;
		if (counter == 5)
		{
			counter = 0;
			data->player->stamina--;
		}
	}
	else if (data->player->speed == 0 && data->player->stamina < 100)
	{
		counter2++;
		if (counter2 == 15)
		{
			counter2 = 0;
			data->player->stamina++;
		}
	}
	if (data->player->speed == 1 && data->player->stamina <= 0)
		data->player->speed = 0;
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
			(double)(UNITS_PER_BOX / 30));
	else
		scaled_direction = vec_scale(p->direction, \
			(double)(UNITS_PER_BOX / STEPS_PER_BOX));
	if (move == BACKWARD)
		rotate_vector(&scaled_direction, degree_to_radian(180));
	else if (move == RIGHT)
		rotate_vector(&scaled_direction, degree_to_radian(90));
	else if (move == LEFT)
		rotate_vector(&scaled_direction, degree_to_radian(-90));
	else if (move != FORWARD)
		error_msg("[move_player] wrong move instruction");
	translate_pt_inplace(scaled_direction, &p->pos_box);
	hit_wall = check_update_box_pos(data);
	update_pos_in_step(p);
	update_pos_in_pix(p);
	return (hit_wall);
}

