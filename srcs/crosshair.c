/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:02:42 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:02:43 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ch_is_on_ennemy(int weapon, t_sprite *sprite)
{
	if (sprite->type + SPRITE >= SPRITE2
	&& g_win_w / 2.0 >= sprite->start_x && g_win_w / 2.0 <= sprite->end_x
	&& ((weapon == MELEE && g_win_h * MELEE_CH_Y >= sprite->start_y
			&& g_win_h * MELEE_CH_Y <= sprite->middle_end_y)
		|| (g_win_h / 2.0 >= sprite->start_y
			&& g_win_h / 2.0 <= sprite->middle_end_y)))
		return (1);
	return (0);
}

int		ch_is_on_ennemies(t_infos *infos)
{
	t_sprite	*sprite;

	sprite = infos->sprite_list;
	while (sprite)
	{
		if (ch_is_on_ennemy(infos->weapon, sprite))
			return (1);
		sprite = sprite->next;
	}
	return (0);
}

/*
** Draw the crosshair in the middle of the screen black by default and red if
** ch is on enemies.
*/

void	draw_crosshair(t_infos *infos)
{
	t_coord		start;
	t_coord		i;
	double		r_x;
	double		r_y;
	int			colo;

	r_x = infos->hud[CH_TEXT].w / (g_win_w / 25.0);
	r_y = infos->hud[CH_TEXT].h / (g_win_h / 25.0);
	start.x = g_win_w / 2.0 - g_win_w / 50.0;
	start.y = g_win_h / 2.0 - g_win_h / 50.0;
	i.x = -1;
	colo = ch_is_on_ennemies(infos) ? 0xff0000 : 0;
	while (++i.x < (int)(infos->hud[CH_TEXT].w / r_x))
	{
		i.y = -1;
		while (++i.y < (int)(infos->hud[CH_TEXT].h / r_y))
		{
			if (infos->hud[CH_TEXT].data[(int)(i.y * r_y)
			* infos->hud[CH_TEXT].w + (int)(i.x * r_x)]
				!= infos->hud[CH_TEXT].data[0])
				infos->data[(start.y + i.y) * g_win_w + (start.x + i.x)] = colo;
		}
	}
}
