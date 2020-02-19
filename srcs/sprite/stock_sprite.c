/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:08:47 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/16 12:29:09 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_size_mult(int type)
{
	if (type + SPRITE == SPRITE2_SMALL)
		return (SMALL);
	else if (type + SPRITE == SPRITE2)
		return (STANDARD);
	else if (type + SPRITE == SPRITE2_BIG)
		return (BIG);
	else
		return (arc4random_uniform(40) / 100.0 + 0.7);
}

void	initialize_sprite(t_sprite *sprite)
{
	sprite->active = 0;
	sprite->already_attacked = 0;
	sprite->object.angle = EAST;
	sprite->object.hp = 1.0;
	sprite->attack_time.tv_sec = 0;
	sprite->move_time.tv_sec = 0;
	sprite->damage = ENEMY_DAMAGE * sprite->size_mult;
}

/*
** Add front sprite to infos->sprite_list and initialize struct.
*/

void	add_sprite(t_infos *infos, int type, t_file *file, t_list *node)
{
	t_sprite	*new;
	int			sprite_texture;

	sprite_texture = SPR_TEXT + (type >= 1 ? 1 : 0);
	if (!(new = malloc(sizeof(*new))))
		ft_map_error(infos, node, "Out of memory");
	new->type = type;
	new->frame = sprite_texture;
	new->size_mult = get_size_mult(type);
	new->object.y = file->map_y * g_win_h + g_win_h / 2.0;
	new->object.x = file->map_x * g_win_h + g_win_h / 2.0;
	new->object.thickness = (infos->texture[sprite_texture].end_r
	- infos->texture[sprite_texture].start_r) * g_win_h * new->size_mult;
	new->object.speed = SPRITE_SPEED * new->size_mult * g_win_h;
	new->next = infos->sprite_list;
	initialize_sprite(new);
	infos->sprite_list = new;
}
