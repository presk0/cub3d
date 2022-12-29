/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:08:38 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/29 11:57:56 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//load textures for minimap and render it
int	minimap_render(t_data *data)
{
	int	a;
	int	b;

	a = 20;
	b = 20;
	data->image->texture_path[0] = mlx_xpm_file_to_image(data->window->mlx, \
		"assets/textures/wall20x20.xpm", &a, &b);
	data->image->texture_path[1] = mlx_xpm_file_to_image(data->window->mlx, \
		"assets/textures/floors.xpm", &a, &b);
	draw_map(data);
	return (0);
}

//generate the 3d world with raycast
void	world_render(t_data *data)
{
	int	i;

	i = 0;
	set_array(data);
	draw_ceiling_floor_mandatory(data);
	while (i < data->window->width)
	{	
		draw_wall_textured(data, i);
		i++;
	}
	
}

//set color red to max value
int	graphics_render(t_data *data)
{
	if (data->menu->game_state == 1)
	{
		if (data->time_state == 0)
			data->time_state = 1;
		else if (data->time_state == 1)
		{
			data->timer = time(NULL);
			data->time_to_lose = time(NULL);
			data->time_state = 2;
		}
		render_game(data);
	}
	else if (data->menu->game_state == 0)
	{
		render_menu(data);
	}
	render_game2(data);
	if (data->time_state == 2 && time(NULL) - data->time_to_lose > 180)
		data->menu->game_state = 2;
	return (0);
}

int	cub3d_render(t_data *data)
{
	mlx_hook(data->window->init, 2, 1L << 0, key_press, data);
	mlx_hook(data->window->init, 3, 1L << 1, key_realese, data);
	mlx_loop_hook(data->window->mlx, graphics_render, data);
	// mlx_hook(data->window->init, 12, 1L << 15, mouse_event, data);
	mlx_hook(data->window->init, 17, 1L << 17, &exit_game, data);
	mlx_loop(data->window->mlx);
	return (0);
}