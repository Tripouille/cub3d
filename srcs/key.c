/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:04:17 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/16 09:01:08 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		tick_event(t_infos *infos)
{
	static t_timespec	old = {0, 0};
	t_timespec			new;

	if (infos->game_over)
		return (1);
	if (!old.tv_sec)
		clock_gettime(CLOCK_REALTIME, &old);
	clock_gettime(CLOCK_REALTIME, &new);
	infos->elapsed_time = timediff(old, new) / 1E9;
	move(infos);
	actualize_angles(infos);
	actualize_doors(infos, infos->door_list, infos->elapsed_time * 1E9);
	if (infos->weapon == MELEE)
		attack_animation(infos);
	else if (infos->weapon == GUN)
		gun_attack_animation(infos);
	else if (infos->weapon == POTATO)
		heal_animation(infos);
	old.tv_nsec = new.tv_nsec;
	old.tv_sec = new.tv_sec;
	actualize_speed(infos);
	if (!infos->game_over)
		draw_threads(infos);
	activate_sprites(infos);
	return (0);
}

int		key_press(int keycode, t_infos *infos)
{
	if (keycode == ESC_KEY)
		ft_exit(infos);
	else if (keycode == W_KEY)
		infos->key.w = 1;
	else if (keycode == S_KEY)
		infos->key.s = 1;
	else if (keycode == A_KEY)
		infos->key.a = 1;
	else if (keycode == D_KEY)
		infos->key.d = 1;
	else if (keycode == LEFT_KEY)
		infos->key.left = 1;
	else if (keycode == RIGHT_KEY)
		infos->key.right = 1;
	else if (keycode == UP_KEY)
		infos->key.up = 1;
	else if (keycode == DOWN_KEY)
		infos->key.down = 1;
	key_press2(keycode, infos);
	tick_event(infos);
	return (0);
}

void	key_press2(int keycode, t_infos *infos)
{
	if (keycode == SHIFT_KEY)
	{
		infos->key.shift = 1;
		infos->player.z = infos->player.thickness / 2.0;
	}
	else if (keycode == E_KEY)
		infos->key.e = 1;
	else if (keycode == SPACE_KEY)
		infos->key.space = 1;
	else if (keycode == ONE_KEY)
		infos->weapon = MELEE;
	else if (keycode == TWO_KEY)
		infos->weapon = GUN;
	else if (keycode == THREE_KEY)
		infos->weapon = POTATO;
}

int		key_release(int keycode, t_infos *infos)
{
	if (keycode == W_KEY)
		infos->key.w = 0;
	else if (keycode == S_KEY)
		infos->key.s = 0;
	else if (keycode == A_KEY)
		infos->key.a = 0;
	else if (keycode == D_KEY)
		infos->key.d = 0;
	else if (keycode == LEFT_KEY)
		infos->key.left = 0;
	else if (keycode == RIGHT_KEY)
		infos->key.right = 0;
	else if (keycode == UP_KEY)
		infos->key.up = 0;
	else if (keycode == DOWN_KEY)
		infos->key.down = 0;
	key_release2(keycode, infos);
	tick_event(infos);
	return (0);
}

void	key_release2(int keycode, t_infos *infos)
{
	if (keycode == SHIFT_KEY)
	{
		infos->key.shift = 0;
		infos->player.z = 0;
	}
	else if (keycode == SPACE_KEY)
		infos->key.space = 0;
	else if (keycode == E_KEY)
	{
		infos->key.e = 0;
		if (infos->weapon == POTATO)
			initialize_times(infos);
	}
}
