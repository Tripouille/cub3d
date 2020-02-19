/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:04:38 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:04:39 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Angle becomes between -45 deg and +45 deg.
*/

double	raycast(t_infos *infos, t_object *source, double angle)
{
	angle = true_angle(angle);
	if (angle > SOUTH + 45.0 || angle <= EAST + 45.0)
		return (raycast_e(infos, source, angle - EAST));
	else if (angle > NORTH - 45.0 && angle <= NORTH + 45.0)
		return (raycast_n(infos, source, angle - NORTH));
	else if (angle > WEST - 45.0 && angle <= WEST + 45.0)
		return (raycast_w(infos, source, angle - WEST));
	else
		return (raycast_s(infos, source, angle - SOUTH));
}

double	raycast_e(t_infos *infos, t_object *source, double angle)
{
	t_ray_infos		ray;

	init_raycast_e(infos, source, angle, &ray);
	while (infos->box_val != WALL
	&& !is_on_door(infos, ray.h_dist < ray.v_dist))
	{
		if (ray.h_dist < ray.v_dist)
			ray.h_dist += g_win_h / ray.sin_angle;
		else
			ray.v_dist += g_win_h / ray.cos_angle;
		infos->box.y = (int)source->y + (ray.h_dist < ray.v_dist ?
		ray.h_dist + 1.0 : ray.v_dist) * ray.sin_angle * ray.dir;
		infos->box.x = (int)source->x + (ray.h_dist < ray.v_dist ?
		ray.h_dist : ray.v_dist + 1.0) * ray.cos_angle;
		infos->box_val = infos->map[infos->box.y
						/ g_win_h][infos->box.x / g_win_h];
	}
	set_wall_orientation(infos, ray.h_dist < ray.v_dist, ray.dir, OEAST);
	return (ray.h_dist < ray.v_dist ? ray.h_dist : ray.v_dist);
}

double	raycast_n(t_infos *infos, t_object *source, double angle)
{
	t_ray_infos		ray;

	init_raycast_n(infos, source, angle, &ray);
	while (infos->box_val != WALL
	&& !is_on_door(infos, ray.h_dist < ray.v_dist))
	{
		if (ray.h_dist < ray.v_dist)
			ray.h_dist += g_win_h / ray.cos_angle;
		else
			ray.v_dist += g_win_h / ray.sin_angle;
		infos->box.y = (int)source->y - (ray.h_dist < ray.v_dist ?
		ray.h_dist + 1.0 : ray.v_dist) * ray.cos_angle;
		infos->box.x = (int)source->x + (ray.h_dist < ray.v_dist ?
		ray.h_dist : ray.v_dist + 1.0) * ray.sin_angle * ray.dir;
		infos->box_val = infos->map[infos->box.y
						/ g_win_h][infos->box.x / g_win_h];
	}
	set_wall_orientation(infos, ray.h_dist < ray.v_dist, ray.dir, ONORTH);
	return (ray.h_dist < ray.v_dist ? ray.h_dist : ray.v_dist);
}

double	raycast_w(t_infos *infos, t_object *source, double angle)
{
	t_ray_infos		ray;

	init_raycast_w(infos, source, angle, &ray);
	while (infos->box_val != WALL
	&& !is_on_door(infos, ray.h_dist < ray.v_dist))
	{
		if (ray.h_dist < ray.v_dist)
			ray.h_dist += g_win_h / ray.sin_angle;
		else
			ray.v_dist += g_win_h / ray.cos_angle;
		infos->box.y = (int)source->y + (ray.h_dist < ray.v_dist ?
		ray.h_dist + 1.0 : ray.v_dist) * ray.sin_angle * -ray.dir;
		infos->box.x = (int)source->x - (ray.h_dist < ray.v_dist ?
		ray.h_dist : ray.v_dist + 1.0) * ray.cos_angle;
		infos->box_val = infos->map[infos->box.y
						/ g_win_h][infos->box.x / g_win_h];
	}
	set_wall_orientation(infos, ray.h_dist < ray.v_dist, ray.dir, OWEST);
	return (ray.h_dist < ray.v_dist ? ray.h_dist : ray.v_dist);
}

double	raycast_s(t_infos *infos, t_object *source, double angle)
{
	t_ray_infos		ray;

	init_raycast_s(infos, source, angle, &ray);
	while (infos->box_val != WALL
	&& !is_on_door(infos, ray.h_dist < ray.v_dist))
	{
		if (ray.h_dist < ray.v_dist)
			ray.h_dist += g_win_h / ray.cos_angle;
		else
			ray.v_dist += g_win_h / ray.sin_angle;
		infos->box.y = (int)source->y + (ray.h_dist < ray.v_dist ?
		ray.h_dist + 1.0 : ray.v_dist) * ray.cos_angle;
		infos->box.x = (int)source->x + (ray.h_dist < ray.v_dist ?
		ray.h_dist : ray.v_dist + 1.0) * ray.sin_angle * -ray.dir;
		infos->box_val = infos->map[infos->box.y
						/ g_win_h][infos->box.x / g_win_h];
	}
	set_wall_orientation(infos, ray.h_dist < ray.v_dist, ray.dir, OSOUTH);
	return (ray.h_dist < ray.v_dist ? ray.h_dist : ray.v_dist);
}
