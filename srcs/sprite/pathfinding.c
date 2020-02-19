/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:08:26 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:09:56 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_abs(int x)
{
	return (x < 0 ? -x : x);
}

double	inverse_move(double move)
{
	return (true_angle(move + 180.0));
}

double	path(t_infos *infos, t_sprite *sprite, double first, double second)
{
	int		o;

	if (min_dist_to_wall(infos, &(sprite->object), first, &o)
			> g_win_h)
	{
		if (first != inverse_move(sprite->last_move))
			return (first);
		else if (min_dist_to_wall(infos, &(sprite->object),
		sprite->last_move, &o) > g_win_h)
			return (sprite->last_move);
	}
	if (min_dist_to_wall(infos, &(sprite->object), second, &o)
			> g_win_h)
	{
		if (second != inverse_move(sprite->last_move))
			return (second);
		else if (min_dist_to_wall(infos, &(sprite->object),
		sprite->last_move, &o) > g_win_h)
			return (sprite->last_move);
	}
	return (-1);
}

/*
** Make enemy move in our direction where our delta is higher.
** Last move prevents enemy to repeat opposite movements.
*/

int		pathfinding(t_infos *infos, t_sprite *sprite)
{
	int					delta_x;
	int					delta_y;

	delta_x = infos->player.x - sprite->object.x;
	delta_y = infos->player.y - sprite->object.y;
	if (ft_abs(delta_x) > ft_abs(delta_y))
	{
		sprite->last_move = path(infos, sprite,
		delta_x > 0 ? EAST : WEST, delta_y > 0 ? SOUTH : NORTH);
		if (sprite->last_move != -1)
			sprite->object.angle = sprite->last_move;
		else
			return (0);
	}
	else
	{
		sprite->last_move = path(infos, sprite,
		delta_y > 0 ? SOUTH : NORTH, delta_x > 0 ? EAST : WEST);
		if (sprite->last_move != -1)
			sprite->object.angle = sprite->last_move;
		else
			return (0);
	}
	return (1);
}
