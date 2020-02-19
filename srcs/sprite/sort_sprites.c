/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:08:31 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:08:31 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			sprite_lst_size(t_sprite *list)
{
	int		size;

	size = 0;
	while (list)
	{
		size++;
		list = list->next;
	}
	return (size);
}

void		sort_array(t_sprite **array, int size)
{
	int			i;
	int			j;
	int			furthest;
	t_sprite	*node;

	i = -1;
	while (++i < size)
	{
		j = i;
		furthest = i;
		while (++j < size)
			if (array[j]->dist > array[furthest]->dist)
				furthest = j;
		if (furthest != i)
		{
			node = array[i];
			array[i] = array[furthest];
			array[furthest] = node;
		}
	}
}

/*
** Copy list in array to sort it, then copies the array back in the list.
** Sort from furthest to closest to draw them
** in accordance with the law of the universe.
*/

void		sort_sprites(t_sprite **list, int size)
{
	t_sprite	*array[size];
	t_sprite	*node;
	int			i;

	if (!size)
		return ;
	i = 0;
	node = *list;
	while (node)
	{
		array[i++] = node;
		node = node->next;
	}
	sort_array(array, size);
	*list = array[0];
	i = -1;
	while (++i < size - 1)
		array[i]->next = array[i + 1];
	array[size - 1]->next = 0;
}
