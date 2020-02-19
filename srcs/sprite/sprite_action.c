/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:16:44 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/16 13:37:38 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Actualize frame of moving sprite.
*/

void	set_sprite_move_frame(t_timespec *move_time, int *sprite_frame)
{
	t_timespec				actual;
	long					diff;

	if (!move_time->tv_sec)
		clock_gettime(CLOCK_REALTIME, move_time);
	clock_gettime(CLOCK_REALTIME, &actual);
	diff = timediff(*move_time, actual);
	if (diff > ENEMY_MOVE_CD)
		clock_gettime(CLOCK_REALTIME, move_time);
	if (diff < ENEMY_MOVE_CD * 1 / 4.0 || diff > ENEMY_MOVE_CD)
		*sprite_frame = SPR2_MOVE1_TEXT;
	else if (diff < ENEMY_MOVE_CD * 2 / 4.0)
		*sprite_frame = SPR2_MOVE2_TEXT;
	else if (diff < ENEMY_MOVE_CD * 3 / 4.0)
		*sprite_frame = SPR2_MOVE3_TEXT;
	else if (diff < ENEMY_MOVE_CD)
		*sprite_frame = SPR2_MOVE4_TEXT;
}

void	damage_player(t_infos *infos, double damage)
{
	system("afplay sounds/yeti_attack.mp3&");
	infos->player.hp -= damage;
	if (infos->player.hp <= 0.01)
		game_over(infos);
}

/*
** Set frame in sprite attack and use damage_player in middle of attack cycle.
*/

void	attack_player(t_infos *infos, t_sprite *sprite)
{
	t_timespec				actual;
	long					diff;

	if (!sprite->attack_time.tv_sec)
		clock_gettime(CLOCK_REALTIME, &(sprite->attack_time));
	clock_gettime(CLOCK_REALTIME, &actual);
	diff = timediff(sprite->attack_time, actual);
	sprite->frame = SPR2_TEXT;
	if (diff > ENEMY_CD)
	{
		clock_gettime(CLOCK_REALTIME, &(sprite->attack_time));
		sprite->already_attacked = 0;
	}
	else if (diff > ENEMY_CD * 3 / 5.0)
	{
		if (!sprite->already_attacked)
		{
			damage_player(infos, sprite->damage);
			sprite->already_attacked = 1;
		}
		sprite->frame = SPR2_ATTACK_TEXT;
	}
}

/*
** Make sprite move or attack for each active sprite.
** Make sprites in our radius or damaged active.
*/

void	activate_sprites(t_infos *infos)
{
	t_sprite	*sprite;

	sprite = infos->sprite_list;
	while (sprite)
	{
		sprite->object.angle = true_angle(sprite->center_ang + 180.0);
		if (sprite->type + SPRITE >= SPRITE2 && sprite->active)
		{
			if (sprite->dist > infos->player.thickness / 2.0
			+ ((ENEMY_RANGE) * 0.9) * g_win_h + sprite->object.thickness / 2.0)
			{
				sprite_move_to_player(infos, sprite);
				sprite->attack_time.tv_sec = 0;
			}
			else
				attack_player(infos, sprite);
		}
		else if ((sprite->dist < SPRITE_ACTIVATION_RADIUS * g_win_h
		|| sprite->object.hp < 0.95) && raycast(infos, &(sprite->object),
										sprite->object.angle) > sprite->dist)
			sprite->active = 1;
		sprite = sprite->next;
	}
}

/*
** Makes sprite move, directly to us if he can or with pseudo pathfinding.
** Add thickness / 2.0 to min_dist_to_wall because min_dist_to_wall
** returns with - thickness / 2.0.;
*/

void	sprite_move_to_player(t_infos *infos, t_sprite *sprite)
{
	int			o;

	if (sprite->dist < sprite->object.thickness / 2.0
	+ min_dist_to_wall(infos, &(sprite->object), sprite->object.angle, &o))
	{
		move_up(infos, &(sprite->object));
		set_sprite_move_frame(&(sprite->move_time), &(sprite->frame));
	}
	else
	{
		if (pathfinding(infos, sprite))
			move_up(infos, &(sprite->object));
		set_sprite_move_frame(&(sprite->move_time), &(sprite->frame));
	}
}
