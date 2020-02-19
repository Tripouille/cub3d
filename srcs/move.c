/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:04:28 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:04:29 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** mod = modificateur d'angle
*/

void	move_up(t_infos *infos, t_object *obj)
{
	int			orientation;
	double		mod;
	double		walkable_dist;

	mod = 0.0;
	if (infos->key.a && obj == &(infos->player))
		mod = 45.0;
	else if (infos->key.d && obj == &(infos->player))
		mod = -45.0;
	walkable_dist = walkable_distance(infos, obj,
					true_angle(obj->angle + mod), &orientation);
	if (walkable_dist > 1.0)
	{
		obj->y -= walkable_dist * sin((obj->angle + mod) * (M_PI / 180.0));
		obj->x += walkable_dist * cos((obj->angle + mod) * (M_PI / 180.0));
	}
	else if (obj == &(infos->player) && orientation != OSPRITE)
		slide(infos, orientation, true_angle(obj->angle + mod));
}

void	move_down(t_infos *infos, t_object *obj)
{
	int			orientation;
	double		mod;
	double		walkable_dist;

	mod = 0.0;
	if (infos->key.a && obj == &(infos->player))
		mod = -45.0;
	else if (infos->key.d && obj == &(infos->player))
		mod = 45.0;
	walkable_dist = walkable_distance(infos, obj,
					true_angle(obj->angle + 180.0 + mod), &orientation);
	if (walkable_dist > 1.0)
	{
		obj->y += walkable_dist * sin((obj->angle + mod) * (M_PI / 180.0));
		obj->x -= walkable_dist * cos((obj->angle + mod) * (M_PI / 180.0));
	}
	else if (obj == &(infos->player) && orientation != OSPRITE)
		slide(infos, orientation, true_angle(obj->angle + 180.0 + mod));
}

void	move_left(t_infos *infos, t_object *obj)
{
	int			orientation;
	double		walkable_dist;

	walkable_dist = walkable_distance(infos, obj,
								true_angle(obj->angle + 90.0), &orientation);
	if (walkable_dist > 1.0)
	{
		obj->y += walkable_dist * sin((obj->angle - NORTH) * (M_PI / 180.0));
		obj->x -= walkable_dist * cos((obj->angle - NORTH) * (M_PI / 180.0));
	}
	else if (obj == &(infos->player) && orientation != OSPRITE)
		slide(infos, orientation, true_angle(obj->angle + 90.0));
}

void	move_right(t_infos *infos, t_object *obj)
{
	int			orientation;
	double		walkable_dist;

	walkable_dist = walkable_distance(infos, obj,
								true_angle(obj->angle - 90.0), &orientation);
	if (walkable_dist > 1.0)
	{
		obj->y -= walkable_dist * sin((obj->angle - NORTH) * (M_PI / 180.0));
		obj->x += walkable_dist * cos((obj->angle - NORTH) * (M_PI / 180.0));
	}
	else if (obj == &(infos->player) && orientation != OSPRITE)
		slide(infos, orientation, true_angle(obj->angle - 90.0));
}

void	move(t_infos *infos)
{
	if (infos->key.w && !infos->key.s)
		move_up(infos, &(infos->player));
	else if (infos->key.s && !infos->key.w)
		move_down(infos, &(infos->player));
	else if (infos->key.a && !infos->key.d)
		move_left(infos, &(infos->player));
	else if (infos->key.d && !infos->key.a)
		move_right(infos, &(infos->player));
}
