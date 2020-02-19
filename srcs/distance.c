/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:03:21 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/16 13:38:07 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Simulate a circle around the sprite of radius of half sprite + half player.
** and return if player is in or not.
*/

int			is_in_sprite_hitbox(t_sprite *sprite, double angle, double radius)
{
	double		start_ang;
	double		end_ang;

	start_ang = true_angle(sprite->center_ang
	+ (asin(radius / sprite->dist) / (M_PI / 180.0)));
	end_ang = true_angle(sprite->center_ang
	- (asin(radius / sprite->dist) / (M_PI / 180.0)));
	if (angle >= end_ang && angle <= start_ang)
		return (1);
	else if (true_angle(angle + 180.0) >= true_angle(end_ang + 180.0)
	&& true_angle(angle + 180.0) <= true_angle(start_ang + 180.0))
		return (1);
	return (0);
}

/*
** Check all sprites to return distance to the closest one.
*/

double		min_dist_to_sprite(t_object *obj,
							t_sprite *sprite, double check_angle)
{
	double		walkable_dist;
	double		occupied_dist;

	walkable_dist = 1E10;
	while (sprite)
	{
		occupied_dist = sprite->object.thickness / 2.0 + obj->thickness / 2.0;
		if (sprite->dist - occupied_dist < walkable_dist
		&& is_in_sprite_hitbox(sprite, true_angle(check_angle), occupied_dist))
			walkable_dist = sprite->dist - occupied_dist;
		sprite = sprite->next;
	}
	return (walkable_dist);
}

/*
** Create a ref from the left of the obj and move to the right of the obj,
** on obj thickness.
*/

double		min_dist_to_wall(t_infos *infos, t_object *obj,
							double check_angle, int *orientation)
{
	t_object	ref;
	double		min_dist;
	double		wall_dist;
	int			i;
	t_ratio		ratio;

	min_dist = 1E10;
	ref.x = obj->x + cos((check_angle + 90) * M_PI / 180) * obj->thickness / 2;
	ref.y = obj->y - sin((check_angle + 90) * M_PI / 180) * obj->thickness / 2;
	ratio.x = (obj->x - ref.x) / (obj->thickness / 2.0);
	ratio.y = (obj->y - ref.y) / (obj->thickness / 2.0);
	i = -1;
	while (++i < obj->thickness / 10.0)
	{
		wall_dist = raycast(infos, &ref, check_angle);
		if (wall_dist < min_dist)
		{
			min_dist = wall_dist;
			*orientation = infos->wall_o;
		}
		ref.x += ratio.x * 10.0;
		ref.y += ratio.y * 10.0;
	}
	return (min_dist - obj->thickness / 2.0);
}

double		walkable_distance(t_infos *infos, t_object *obj,
								double check_angle, int *orientation)
{
	double	min_dist;

	if (obj != &(infos->player))
		return (obj->speed * infos->elapsed_time);
	min_dist = min_dist_to_wall(infos, obj, check_angle, orientation);
	if (min_dist < obj->speed * infos->elapsed_time)
		return (min_dist);
	min_dist = min_dist_to_sprite(obj, infos->sprite_list, check_angle);
	if (min_dist < obj->speed * infos->elapsed_time)
	{
		*orientation = OSPRITE;
		return (min_dist);
	}
	return (obj->speed * infos->elapsed_time);
}
