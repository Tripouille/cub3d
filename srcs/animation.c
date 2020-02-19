/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:02:17 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:02:22 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		copy_time(t_timespec *dst, const t_timespec *src)
{
	dst->tv_sec = src->tv_sec;
	dst->tv_nsec = src->tv_nsec;
}

void		gun_attack_animation(t_infos *infos)
{
	t_timespec				actual;
	long					diff;

	clock_gettime(CLOCK_REALTIME, &actual);
	if (!infos->gun_time.tv_sec && infos->key.e)
		copy_time(&infos->gun_time, &actual);
	diff = timediff(infos->gun_time, actual);
	if (diff > GUN_CD && infos->key.e)
	{
		copy_time(&infos->gun_time, &actual);
		infos->already_attacked = 0;
	}
	else if (diff < GUN_CD / 6.0 || diff > GUN_CD)
		infos->weapon_frame = GUN1_TEXT;
	else if (diff < GUN_CD * 2 / 6.0)
		infos->weapon_frame = GUN2_TEXT;
	else if (diff < GUN_CD * 3 / 6.0)
		infos->weapon_frame = GUN3_TEXT;
	else if (diff < GUN_CD * 4 / 6.0)
		infos->weapon_frame = GUN4_TEXT;
	else if (diff < GUN_CD * 5 / 6.0)
		infos->weapon_frame = GUN3_TEXT;
	if (diff > GUN_CD / 6.0 && diff < GUN_CD && !infos->already_attacked
		&& (infos->already_attacked = 1))
		gun_attack(infos, PLAYER_DAMAGE / 2.0);
}

void		attack_animation(t_infos *infos)
{
	t_timespec				actual;
	long					diff;

	clock_gettime(CLOCK_REALTIME, &actual);
	if (!infos->melee_time.tv_sec && infos->key.e)
		copy_time(&infos->melee_time, &actual);
	diff = timediff(infos->melee_time, actual);
	if (diff > ATTACK_CD && infos->key.e)
	{
		copy_time(&infos->melee_time, &actual);
		infos->already_attacked = 0;
	}
	else if (diff < ATTACK_CD / 5.0 || diff > ATTACK_CD)
		infos->weapon_frame = WEAPON1_TEXT;
	else if (diff < ATTACK_CD * 2 / 5.0)
		infos->weapon_frame = WEAPON2_TEXT;
	else if (diff < ATTACK_CD * 3 / 5.0)
		infos->weapon_frame = WEAPON3_TEXT;
	else if (diff < ATTACK_CD * 4 / 5.0)
		infos->weapon_frame = WEAPON2_TEXT;
	else if (diff < ATTACK_CD)
		infos->weapon_frame = WEAPON1_TEXT;
	if (diff > ATTACK_CD * 2 / 5.0 && diff < ATTACK_CD
	&& !infos->already_attacked && (infos->already_attacked = 1))
		melee_attack(infos, PLAYER_DAMAGE);
}

void		heal_animation(t_infos *infos)
{
	t_timespec				actual;
	long					diff;

	clock_gettime(CLOCK_REALTIME, &actual);
	if (!infos->heal_time.tv_sec && infos->key.e)
		copy_time(&infos->heal_time, &actual);
	diff = timediff(infos->heal_time, actual);
	if (diff > HEAL_CD && infos->key.e)
	{
		copy_time(&infos->heal_time, &actual);
		if (infos->player.hp == 1.0)
			return ;
		system("afplay -q 1 -v 3 sounds/chips.mp3&");
		infos->player.hp += HEAL;
		if (infos->player.hp > 1.0)
			infos->player.hp = 1.0;
	}
}
