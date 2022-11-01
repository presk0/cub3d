/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 16:10:30 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_exit(t_data *data, int exit_code)
{
	int	i;

	if (data)
	{
		if (data->line)
			free(data->line);
		if (data->line_split)
			ft_free_split(&data->line_split);
		if (data->map)
			ft_free_split(&data->map);
		if (data->player)
			free(data->player);
		if (data->blocks)
			free(data->blocks);
		if (data->map_cases)
			free(data->map_cases);
		if (data->cam)
			free(data->cam);
		if (data->image)
		{
			i = 0;
			while (i < NB_TEXTURES)
			{
				if (data->image->texture_path[i])
					free(data->image->texture_path[i]);
				i++;
			}
			free(data->image);
		}
		free(data);
	}
	exit(exit_code);
}

void	exit_msg(t_data *data, char *msg, int ret_exit)
{
	error_msg(msg);
	clean_exit(data, ret_exit);
}
