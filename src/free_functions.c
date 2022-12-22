/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 00:11:02 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/21 15:11:39 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void free_data(t_data *data)
{
	free(data->cam->beam);
	free(data->cam);
	free(data->map_cases);
	free(data->blocks);
	free(data->player);
	free(data->image);
	// free(data->window->mlx);
	free(data->window);
}
void free_wall_textures(t_data *data)
{
	int i;

	i = 0;
	while (i < NB_TEXTURES)
	{
		mlx_destroy_image(data->window->mlx, data->wall_textures[i]->img);
		free(data->wall_textures[i]);
		i++;
	}
}

void free_texture_path(t_data *data)
{
	int i;

	i = 0;
	while (i < 4)
	{
		free(data->image->texture_path[i]);
		i++;
	}
}

void	free_menu(t_data *data)
{
	int	i;

	i = 0;
	while (i < NB_MENU_IMG)
	{
		mlx_destroy_image(data->window->mlx, data->menu->background[i]->img);
		free(data->menu->background[i]);
		i++;
	}
	free(data->menu);
}

void	free_bonus_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		mlx_destroy_image(data->window->mlx, data->bonus_textures[i].img);
		i++;
	}
	free(data->bonus_textures);
}

void	free_test(t_data *data)
{
	ft_free_split(&data->map);
}

void	free_everything(t_data *data)
{
	mlx_destroy_image(data->window->mlx, data->img->img);
	free(data->key_status);
	free_bonus_textures(data);
	free_menu(data);
	free(data->img);
	ft_free_split(&data->map);
	free_texture_path(data);
	free_wall_textures(data);
	mlx_destroy_window(data->window->mlx, data->window->init);
	mlx_destroy_display(data->window->mlx);
	free(data->window->mlx);
	free_data(data);
	free(data);
}