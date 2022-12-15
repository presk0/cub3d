/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 20:45:24 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/15 03:44:27 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_point	units_pos_to_minimap_pos(t_data *data, t_point absolute_position)
{
	t_point		pos_for_map;
	double		u;
	double		wall_size;

	(void)data;
	u = (double)UNITS_PER_BOX;
	wall_size = (double)WALL_SIZE + 1;
	pos_for_map.x = wall_size * ((((double)absolute_position.x) / u));
	pos_for_map.y = wall_size * ((((double)absolute_position.y) / u));
	return (pos_for_map);
}

int	load_window(t_data *data)
{
	t_window	*window;

	window = data->window;
	data->img = malloc(sizeof(t_img_data));
	window->height = SCREEN_HEIGHT;
	window->width = SCREEN_WIDTH;
	data->img->img = mlx_new_image(window->mlx, window->width, window->height);
	window->init = mlx_new_window(window->mlx, \
		window->width, window->height, "Cub3d");
	data->img->line_len = data->img->line_len >> 2;
	data->img->address = (int *)mlx_get_data_addr(data->img->img, \
		&data->img->bpp, &data->img->line_len, &data->img->endian);
	load_menu(data);
	return (0);
}
