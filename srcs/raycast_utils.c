/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:04:42 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:04:43 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycast_e(t_infos *infos, t_object *source,
						double angle, t_ray_infos *ray)
{
	angle = angle == 0.0 ? 0.01 : angle;
	ray->cos_angle = cos(angle * (M_PI / 180.0));
	ray->sin_angle = sin(angle * (M_PI / 180.0));
	ray->dir = ray->sin_angle > 0 ? LEFT : RIGHT;
	if (ray->sin_angle < 0)
		ray->sin_angle *= -1.0;
	if (ray->dir == LEFT)
		ray->h_dist = (int)source->y % g_win_h / ray->sin_angle;
	else
		ray->h_dist = (g_win_h - (int)source->y % g_win_h) / ray->sin_angle;
	ray->v_dist = (g_win_h - (int)source->x % g_win_h) / ray->cos_angle;
	infos->box.y = (int)source->y + (ray->h_dist < ray->v_dist ?
				ray->h_dist + 1.0 : ray->v_dist) * ray->sin_angle * ray->dir;
	infos->box.x = (int)source->x + (ray->h_dist < ray->v_dist ?
				ray->h_dist : ray->v_dist + 1.0) * ray->cos_angle;
	infos->box_val = infos->map[infos->box.y / g_win_h][infos->box.x / g_win_h];
}

void	init_raycast_n(t_infos *infos, t_object *source,
						double angle, t_ray_infos *ray)
{
	angle = angle == 0.0 ? 0.01 : angle;
	ray->cos_angle = cos(angle * (M_PI / 180.0));
	ray->sin_angle = sin(angle * (M_PI / 180.0));
	ray->dir = ray->sin_angle > 0 ? LEFT : RIGHT;
	if (ray->sin_angle < 0)
		ray->sin_angle *= -1.0;
	if (ray->dir == LEFT)
		ray->v_dist = (int)source->x % g_win_h / ray->sin_angle;
	else
		ray->v_dist = (g_win_h - (int)source->x % g_win_h) / ray->sin_angle;
	ray->h_dist = (int)source->y % g_win_h / ray->cos_angle;
	infos->box.y = (int)source->y - (ray->h_dist < ray->v_dist ?
	ray->h_dist + 1.0 : ray->v_dist) * ray->cos_angle;
	infos->box.x = (int)source->x + (ray->h_dist < ray->v_dist ?
	ray->h_dist : ray->v_dist + 1.0) * ray->sin_angle * ray->dir;
	infos->box_val = infos->map[infos->box.y / g_win_h][infos->box.x / g_win_h];
}

void	init_raycast_w(t_infos *infos, t_object *source,
						double angle, t_ray_infos *ray)
{
	angle = angle == 0.0 ? 0.01 : angle;
	ray->cos_angle = cos(angle * (M_PI / 180.0));
	ray->sin_angle = sin(angle * (M_PI / 180.0));
	ray->dir = ray->sin_angle > 0 ? LEFT : RIGHT;
	if (ray->sin_angle < 0)
		ray->sin_angle *= -1.0;
	if (ray->dir == LEFT)
		ray->h_dist = (g_win_h - (int)source->y % g_win_h) / ray->sin_angle;
	else
		ray->h_dist = (int)source->y % g_win_h / ray->sin_angle;
	ray->v_dist = (int)source->x % g_win_h / ray->cos_angle;
	infos->box.y = (int)source->y + (ray->h_dist < ray->v_dist ?
	ray->h_dist + 1.0 : ray->v_dist) * ray->sin_angle * -ray->dir;
	infos->box.x = (int)source->x - (ray->h_dist < ray->v_dist ?
	ray->h_dist : ray->v_dist + 1.0) * ray->cos_angle;
	infos->box_val = infos->map[infos->box.y / g_win_h][infos->box.x / g_win_h];
}

void	init_raycast_s(t_infos *infos, t_object *source,
						double angle, t_ray_infos *ray)
{
	angle = angle == 0.0 ? 0.01 : angle;
	ray->cos_angle = cos(angle * (M_PI / 180.0));
	ray->sin_angle = sin(angle * (M_PI / 180.0));
	ray->dir = ray->sin_angle > 0 ? LEFT : RIGHT;
	if (ray->sin_angle < 0)
		ray->sin_angle *= -1.0;
	if (ray->dir == LEFT)
		ray->v_dist = (g_win_h - (int)source->x % g_win_h) / ray->sin_angle;
	else
		ray->v_dist = (int)source->x % g_win_h / ray->sin_angle;
	ray->h_dist = (g_win_h - (int)source->y % g_win_h) / ray->cos_angle;
	infos->box.y = (int)source->y + (ray->h_dist < ray->v_dist ?
	ray->h_dist + 1.0 : ray->v_dist) * ray->cos_angle;
	infos->box.x = (int)source->x + (ray->h_dist < ray->v_dist ?
	ray->h_dist : ray->v_dist + 1.0) * ray->sin_angle * -ray->dir;
	infos->box_val = infos->map[infos->box.y / g_win_h][infos->box.x / g_win_h];
}

void	set_wall_orientation(t_infos *infos, int is_horizontal,
								int dir, int raycast_o)
{
	if (raycast_o == OEAST && is_horizontal)
		infos->wall_o = dir == LEFT ? ONORTH : OSOUTH;
	else if (raycast_o == ONORTH && !is_horizontal)
		infos->wall_o = dir == LEFT ? OWEST : OEAST;
	else if (raycast_o == OWEST && is_horizontal)
		infos->wall_o = dir == LEFT ? OSOUTH : ONORTH;
	else if (raycast_o == OSOUTH && !is_horizontal)
		infos->wall_o = dir == LEFT ? OEAST : OWEST;
	else
		infos->wall_o = raycast_o;
}
