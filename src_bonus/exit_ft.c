/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/12/29 13:59:37 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* where all pointers are cleaned, especially in a emergency exit */
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
		{
			if (data->cam->beam)
				free(data->cam->beam);
			i = 0;
			while (i < CAM_QUALITY)
				ft_lstclear(&data->cam->array[i++].obstacles_ls, free);
			free(data->cam);
		}
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

int	exit_game(t_data *data)
{
	free_everything(data);
	exit(0);
}