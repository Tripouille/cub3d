/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slide.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:04:51 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:04:51 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			can_slide(t_infos *infos, int o, double angle)
{
	double		check_angle;

	if (angle < o * 90.0
	|| (o == OEAST && angle > SOUTH))
		check_angle = true_angle(o * 90.0 - 90.0);
	else
		check_angle = true_angle(o * 90.0 + 90.0);
	if (raycast(infos, &(infos->player), check_angle)
	- infos->player.thickness / 2.0 < infos->player.speed * infos->elapsed_time)
		return (0);
	if (min_dist_to_sprite(&(infos->player), infos->sprite_list, check_angle)
									< infos->player.speed * infos->elapsed_time)
		return (0);
	return (1);
}

void		slide(t_infos *infos, int o, double angle)
{
	if (!can_slide(infos, o, angle))
		return ;
	if (o == OEAST)
	{
		if (angle > WEST)
			infos->player.y += infos->player.speed * infos->elapsed_time
								* (EAST - angle + 360.0) / 90.0;
		else
			infos->player.y += infos->player.speed * infos->elapsed_time
								* (EAST - angle) / 90.0;
	}
	else if (o == ONORTH)
		infos->player.x += infos->player.speed * infos->elapsed_time
						* (NORTH - angle) / 90.0;
	else if (o == OWEST)
		infos->player.y -= infos->player.speed * infos->elapsed_time
						* (WEST - angle) / 90.0;
	else if (o == OSOUTH)
		infos->player.x -= infos->player.speed * infos->elapsed_time
						* (SOUTH - angle) / 90.0;
}
