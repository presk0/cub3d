/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/11/07 19:47:31 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_delta_distance(t_data *data)
{
	t_ray 	*ray;
	t_cam	*cam;
	double	u;
	
	cam = data->cam;
	ray = cam->beam;
	u = (double)UNITS_PER_BOX;
	ray->direction_len = vec_len(ray->direction);
	if (ray->direction.x)
		ray->delta_distances.x = ray->direction_len * u / fabs(ray->direction.x);
	else
		ray->delta_distances.x = 2147483647;
	if (ray->direction.y)
		ray->delta_distances.y = ray->direction_len * u / fabs(ray->direction.y);
	else
		ray->delta_distances.y = 2147483647;
	ray->vector_deltaX = vec_scale(ray->direction, ray->delta_distances.x / ray->direction_len);
	ray->vector_deltaY = vec_scale(ray->direction, ray->delta_distances.y / ray->direction_len);
}

/*
  not sure of the calcul, but set the distance to the next_case 
 	delta_dist MUST BE UPDATED
	*/
void	set_side_distance(t_data *data)
{
	t_cam		*cam;
	t_ray		*ray;
	t_player	*player;
	double		u;
	
	cam = data->cam;
	ray = cam->beam;
	player = data->player;
	u = (double)UNITS_PER_BOX;
	if (ray->direction.x > 0)
		ray->side_distances.x = ray->delta_distances.x * ((double)(u - player->pos_box.x) / u);
	else
		ray->side_distances.x = ray->delta_distances.x * ((double)(1 + player->pos_box.x) / u);
	if (ray->direction.y > 0)
		ray->side_distances.y = ray->delta_distances.y * ((double)(u - player->pos_box.y) / u);
	else
		ray->side_distances.y = ray->delta_distances.y * ((double)(1 + player->pos_box.y) / u);
	ray->vector_sideX = vec_scale(ray->direction, ray->side_distances.x / ray->direction_len);
	ray->vector_sideY = vec_scale(ray->direction, ray->side_distances.y / ray->direction_len);
}

void	set_beam(t_data *data, t_point ray_position[2])
{
	ray_position[_x] = data->player->pos_in_pix;
	ray_position[_y] = data->player->pos_in_pix;
	set_delta_distance(data);
	set_side_distance(data);
}

int	first_step(t_data *data, t_point ray_position[2], double len[2])
{
	t_ray	*ray;
	char	next_cases[2];
	int		closest;

	ray = data->cam->beam;
	closest = _y;
	len[_x] = ray->side_distances.x;
	len[_y] = ray->side_distances.y;
	if (len[_x] > 0 && len[_x] < len [_y])
		closest = _x;
	translate_pt(ray->vector_sideX, &ray_position[_x]);
	translate_pt(ray->vector_sideY, &ray_position[_y]);
	next_cases[closest] = pix_pos_to_map_case(data, ray_position[closest]);
	if (next_cases[closest] == WALL)
		return (closest);
	if (still_in_map(data, ray_position[!closest]))
		next_cases[!closest] = pix_pos_to_map_case(data, ray_position[!closest]);
	if (next_cases[!closest] == WALL)
		return (!closest);
	return (-1);
}

int	beam_step(t_data *data, t_point ray_position[2], double len[2])
{
	t_ray	*ray;

	ray = data->cam->beam;
	if (len[_x] < len[_y] && len[_x] > 0)
	{
		translate_pt(ray->vector_deltaX, &ray_position[_x]);
		len[_x] += ray->delta_distances.x;
		if (still_in_map(data, ray_position[_x]))
		{
			if (pix_pos_to_map_case(data, ray_position[_x]) == WALL)
				return (_x);
		}
		else
			return (-2);
	}
	else if (len[_y] > 0)
	{
		translate_pt(ray->vector_deltaY, &ray_position[_y]);
		len[_y] += ray->delta_distances.y;
		if (still_in_map(data, ray_position[_y]))
		{
			if (pix_pos_to_map_case(data, ray_position[_y]) == WALL)
				return (_y);
		}
		else
			return (-3);
	}
	else
	{
		translate_pt(ray->vector_deltaX, &ray_position[_x]);
		len[_x] += ray->delta_distances.x;
		if (still_in_map(data, ray_position[_x]))
		{
			if (pix_pos_to_map_case(data, ray_position[_x]) == WALL)
				return (_x);
		}
		else
			return (-2);
	}
	return (-1);
}

void set_dist_from_plan(t_data *data)
{
	t_vector	cam_dir;
	t_vector	v_pos;
	t_vector	line[2];

	cam_dir = data->cam->plane_dir;
	v_pos.x = (double)data->player->pos_in_pix.x;
	v_pos.y = (double)data->player->pos_in_pix.y;
	line[0] = v_pos;
	translate_vector_as_pt(cam_dir, &v_pos);
	line[1] = v_pos;
	data->cam->beam->dist_from_plan = distance_line_to_point(line, 	data->cam->beam->hit_point);
}

void	raysult(t_data *data, t_point ray_position[2], double len[2], int side_hit)
{
	t_cam		*cam;
	t_ray		*ray;

	cam = data->cam;
	ray = cam->beam;
	ray->len = len[side_hit];
	if (side_hit == _y)
	{
		if (ray->direction.y > 0)
			ray->side = SOUTH;
		else
			ray->side = NORTH;
	}
	else
	{
		if (ray->direction.x < 0)
			ray->side = WEST;
		else
			ray->side = EAST;
	}
	ray->hit_point = ray_position[side_hit];
	set_dist_from_plan(data);
}

/*
	return absulute point (in UNIT_PER_BOX) hitting the wall
	delta_distance must be set before side distance
*/
t_ray	beam(t_data *data)
{
	t_point		ray_position[2]; // x and y
	double		len[2];
	t_cam		*cam;
	int			wall_hit;

	cam = data->cam;
	set_beam(data, ray_position);
	wall_hit = first_step(data, ray_position, len);
	while (wall_hit == -1)
	{
		if (wall_hit == -2)
			len[_x] = -1;
		else if (wall_hit == -3)
			len[_y] = -1;
		wall_hit = beam_step(data, ray_position, len);
	}
	if (wall_hit != -2)
		raysult(data, ray_position, len, wall_hit);
	return (*(cam->beam));
}

void	set_arRay(t_data *data)
{
	t_ray	*ray;
	t_cam	*cam;
	int		i_ray;

	init_cam_vector(data);
	cam = data->cam;
	ray = cam->beam;
	i_ray = 0;
	while (i_ray < CAM_QUALITY)
	{
		cam->arRay[i_ray] = beam(data);
		translate_vector_as_pt(cam->plane_dir, &ray->direction);
		i_ray++;
	}
}
