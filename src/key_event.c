/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:57:02 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/01 18:23:35 by dpaulino         ###   ########.fr       */
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

void	init_key_status(t_data *data)
{
	data->key_status = malloc(sizeof(t_key_status));
	data->key_status->a = 0;
	data->key_status->d = 0;
	data->key_status->w = 0;
	data->key_status->s = 0;
	data->key_status->left = 0;
	data->key_status->right = 0;
}

int	key_press(int key, t_data *data)
{
	if (key == KEY_W && data->menu->start == 1 && data->menu->off == 1)
	{
		data->menu->on = 1;
		data->menu->off = 0;
	}
	if (key == KEY_W && data->menu->on == 1)
		data->key_status->w = 1;
    else if (key == KEY_S && data->menu->on == 1)
		data->key_status->s = 1;
    else if (key == KEY_A && data->menu->on == 1)
		data->key_status->a = 1;
    else if (key == KEY_D && data->menu->on == 1)
		data->key_status->d = 1;
    else if (key == KEY_RIGHT && data->menu->on == 1)
		data->key_status->right = 1;
	else if (key ==KEY_LEFT && data->menu->on == 1)
		data->key_status->left = 1;
	else if (key == KEY_ESC)
		exit_game(data);
	return (0);
}
/* player_struct modified */
int	key_realese(int key, t_data *data)
{
	if (key == KEY_W && data->menu->on == 1)
		data->key_status->w = 0;
    else if (key == KEY_S && data->menu->on == 1)
		data->key_status->s = 0;
    else if (key == KEY_A && data->menu->on == 1)
		data->key_status->a = 0;
    else if (key == KEY_D && data->menu->on == 1)
		data->key_status->d = 0;
    else if (key == KEY_RIGHT && data->menu->on == 1)
		data->key_status->right = 0;
	else if (key ==KEY_LEFT && data->menu->on == 1)
		data->key_status->left = 0;
	return (0);
}


int exit_game(t_data *data)
{
    //free
    (void)data;
    clean_exit(data, 0);
	return (0);
}

