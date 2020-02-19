/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:05:56 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:05:57 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	lst_purge(t_list *head)
{
	if (!head)
		return ;
	lst_purge(head->next);
	free(head->content);
	free(head);
}

void	lst_add_back(t_infos *infos, t_list **head, void *content)
{
	static t_list	*last = 0;
	t_list			*new;

	if (!(new = malloc(sizeof(*new))))
	{
		lst_purge(*head);
		ft_error(infos, "Malloc failed in parsing.");
	}
	new->content = content;
	new->next = 0;
	if (!*head)
		*head = new;
	else
		last->next = new;
	last = new;
}

int		lst_size(t_list *list)
{
	return (list ? 1 + lst_size(list->next) : 0);
}
