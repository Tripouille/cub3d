/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:02:09 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:28:03 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Lower the speed when crouch or eating potato.
*/

void	actualize_speed(t_infos *infos)
{
	if ((infos->key.shift)
	|| (infos->weapon == POTATO && infos->key.e && infos->player.hp < 1.0))
		infos->player.speed = g_win_h * PLAYER_SPEED / 2.0;
	else
		infos->player.speed = g_win_h * PLAYER_SPEED;
}

void	actualize_angles(t_infos *infos)
{
	if (infos->key.left)
		infos->player.angle = true_angle(infos->player.angle
								+ ANGLE_SPEED * infos->elapsed_time);
	if (infos->key.right)
		infos->player.angle = true_angle(infos->player.angle
								- ANGLE_SPEED * infos->elapsed_time);
	infos->player.angle += infos->player.angle < 0.01 ? 0.01 : 0.0;
	if (infos->key.up && infos->player.v_angle
						+ Z_ANGLE_SPEED * infos->elapsed_time < Z_ANGLE_MAX)
	{
		infos->player.v_angle += Z_ANGLE_SPEED * infos->elapsed_time;
		infos->player.angle_z = -sin(infos->player.v_angle * 90.0
					/ Z_ANGLE_MAX * (M_PI / 180.0)) * infos->player.thickness;
	}
	if (infos->key.down && infos->player.v_angle
						- Z_ANGLE_SPEED * infos->elapsed_time > -Z_ANGLE_MAX)
	{
		infos->player.v_angle -= Z_ANGLE_SPEED * infos->elapsed_time;
		infos->player.angle_z = -sin(infos->player.v_angle * 90.0
					/ Z_ANGLE_MAX * (M_PI / 180.0)) * infos->player.thickness;
	}
}
