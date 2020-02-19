/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:03:31 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/16 09:06:16 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Actualize the door gap for the display, and activate the door.
*/

void	actualize_doors(t_infos *infos, t_door *door, double elapsed_time)
{
	double	dist;

	while (door)
	{
		dist = raycast(infos, &(infos->player), infos->player.angle);
		if (door->status == OPEN && door->gap < 1.0)
		{
			door->gap += elapsed_time / (DOOR_CD);
			if (door->gap > 1.0)
				door->gap = 1.0;
		}
		else if (infos->key.space && infos->box_val == DOOR
		&& infos->box.x / g_win_h == door->pos.x
		&& infos->box.y / g_win_h == door->pos.y
		&& dist < DOOR_RADIUS * g_win_h)
		{
			system("afplay -q 1 sounds/open_door.mp3&");
			door->status = OPEN;
		}
		door = door->next;
	}
}

void	add_door(t_infos *infos, t_file *file, t_list *node)
{
	t_door	*new;

	if (!(new = malloc(sizeof(*new))))
		ft_map_error(infos, node, "Out of memory");
	new->pos.y = file->map_y;
	new->pos.x = file->map_x;
	new->gap = 0.0;
	new->status = CLOSED;
	new->next = infos->door_list;
	infos->door_list = new;
}

/*
** Return the correct door.
*/

t_door	*get_door(t_infos *infos)
{
	t_door	*door;

	door = infos->door_list;
	while (door && (door->pos.x != infos->box.x / g_win_h
					|| door->pos.y != infos->box.y / g_win_h))
		door = door->next;
	return (door);
}

/*
** Check if the ray hit the door or not depend on the gap.
*/

int		is_on_door(t_infos *infos, int is_horizontal)
{
	t_door		*door;
	double		ratio;

	if (infos->box_val != DOOR)
		return (0);
	door = get_door(infos);
	if (is_horizontal)
		ratio = (infos->box.x % g_win_h) / (double)g_win_h;
	else
		ratio = (infos->box.y % g_win_h) / (double)g_win_h;
	if (ratio > door->gap)
		return (1);
	return (0);
}
