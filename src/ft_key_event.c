/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:57:02 by dpaulino          #+#    #+#             */
/*   Updated: 2022/11/03 12:40:47 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int fix_ang(int a)
{
	if(a > 359)
	{
		a -= 360;
	}
	if(a < 0)
	{
		a += 360;
	}
	return (a);
}

/* player_struct modified */
int	key_event(int key, t_data *data)
{
	t_player *player;

	fprintf(stderr, "[key_event] %d pressed\n", key);
	player = data->player;
	(void)player;
	if (key == KEY_W)
	{
		printf("player move up\n");
		move_player(data, FORWARD);
	}
    else if (key == KEY_S)
	{
		printf("player move down\n");
		move_player(data, BACKWARD);
	}
    else if (key == KEY_A)
	{
		move_player(data, LEFT);
		printf("player move left\n");
	}
    else if (key == KEY_D)
	{
		move_player(data, RIGHT);
		printf("player move right\n");
	}
    else if (key == KEY_RIGHT)
    {
		printf("player move left\n");
		player->angle -= 5;
		player->angle = fix_ang(player->angle);
		player->direction.x = cos(degree_to_radian(player->angle)) * 2;
		player->direction.y = -sin(degree_to_radian(player->angle)) * 2;
    }
	else if (key ==KEY_LEFT)
    {
		printf("player move right\n");
		player->angle += 5;
		player->angle = fix_ang(player->angle);
		player->direction.x = cos(degree_to_radian(player->angle)) * 2;
		player->direction.y = -sin(degree_to_radian(player->angle)) * 2;
		
    }
    mlx_clear_window(data->window->mlx, data->window->init);
	return (0);
}

int exit_game(t_data *data)
{
    //free
    (void)data;
    clean_exit(data, 0);
	return (0);
}

