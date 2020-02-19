/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:02:26 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:02:28 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Damage the sprite then if he dies remove it from the list,
** actualize the previous if he doesn't die.
*/

void		hit(t_infos *infos, t_sprite **sprite_prev,
						t_sprite *sprite, double damage)
{
	sprite->object.hp -= damage / sprite->size_mult;
	if (sprite->object.hp <= 0.01)
	{
		if (*sprite_prev)
			(*sprite_prev)->next = sprite->next;
		else
			infos->sprite_list = sprite->next;
		free(sprite);
		sprite_dies(infos);
	}
	else
		*sprite_prev = sprite;
}

/*
** Damage sprite if crosshair is on a sprite.
** If multiple sprite, take the closest for target.
*/

void		gun_attack(t_infos *infos, double damage)
{
	t_sprite	*sprite;
	t_sprite	*prev;
	t_sprite	*closest;
	t_sprite	*closest_prev;

	system("afplay sounds/pistol_shot.mp3&");
	sprite = infos->sprite_list;
	closest = 0;
	closest_prev = 0;
	prev = 0;
	while (sprite)
	{
		if (ch_is_on_ennemy(GUN, sprite))
		{
			closest_prev = prev;
			closest = sprite;
		}
		prev = sprite;
		sprite = sprite->next;
	}
	if (closest)
		hit(infos, &closest_prev, closest, damage);
}

/*
** Damage all sprites in front of player.
*/

void		melee_attack(t_infos *infos, double damage)
{
	t_sprite	*sprite;
	t_sprite	*next_sprite;
	t_sprite	*prev;
	int			hit_nb;

	sprite = infos->sprite_list;
	hit_nb = 0;
	prev = 0;
	while (sprite)
	{
		next_sprite = sprite->next;
		if (sprite->dist - sprite->object.thickness / 2.0
			< g_win_h * MELEE_RANGE
		&& ch_is_on_ennemy(MELEE, sprite) && ++hit_nb)
			hit(infos, &prev, sprite, damage);
		else
			prev = sprite;
		sprite = next_sprite;
	}
	if (hit_nb)
		system("afplay -q 1 -v 2 sounds/fork_hit.mp3&");
}
