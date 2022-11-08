/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/10/26 17:33:57 by suplayerko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

 t_data	*malloc_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		clean_exit(data, -1);
	data->image = malloc(sizeof(t_image));
	if (!data->image)
		clean_exit(data, -1);
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		clean_exit(data, -1);
	data->blocks = ft_strdup(IS_BLOCK);
	if (!data->blocks)
		clean_exit(data, -1);
	data->map_cases = ft_strdup(MAPCASES);
	if (!data->map_cases)
		clean_exit(data, -1);
	data->cam = malloc(sizeof(t_cam));
	if (!data->cam)
		clean_exit(data, -1);
	return (data);
}

void	test_function(t_data *data)
{
	redir_debug_file_logs(data, DEBUG_LOG_FILENAME, PLAYER);
	move_player(data, LEFT);
	redir_debug_file_logs(data, DEBUG_LOG_FILENAME, PLAYER);
}

int	main(int argc, char *argv[])
{
	t_image		img;
	t_data		*data;

	(void)img;
	data = NULL;
	if (argc != 2)
	{
		error_msg("Needs a path to the map file only");
		clean_exit(data, -2);
	}
	else
	{
		data = malloc_data();
		parse_file(argv[1],  data);
		data->window = malloc(sizeof(t_window));
		//data->player = malloc(sizeof(t_player));
		////player_init(data->map, data->player);
		window_init(data->window);
		/* I dont understand 2, 1L << 0, */
		mlx_hook(data->window->init, 2, 1L << 0, &key_event, data);
		mlx_loop_hook(data->window->mlx, render_map_2d, data);
		mlx_hook(data->window->init, 17, 1L << 17, &exit_game, data);
		mlx_loop(data->window->mlx);
	}
	clean_exit(data, 0);
}
