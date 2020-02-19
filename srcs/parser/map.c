/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:06:02 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:06:02 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_map(t_file *file, t_infos *infos, char *buffer)
{
	t_list	*head;
	char	*line;
	int		r;
	int		size;

	if (!*buffer)
	{
		free(buffer);
		ft_error(infos, "Missing map.");
	}
	head = 0;
	lst_add_back(infos, &head, buffer);
	while ((r = get_next_line(file->fd, &line)) == 1)
		lst_add_back(infos, &head, line);
	if (r == -1)
		ft_map_error(infos, head, "Reading failed in parsing.");
	if (*line)
		lst_add_back(infos, &head, line);
	else
		free(line);
	if ((size = lst_size(head)) < 3)
		ft_map_error(infos, head, "Map is too small.");
	if (!(infos->map = ft_calloc(sizeof(char*), size + 1)))
		ft_map_error(infos, head, "Malloc failed in parsing.");
	fill_map(head, infos, file);
}

void	fill_map(t_list *node, t_infos *infos, t_file *file)
{
	t_list	*tmp;
	int		i;

	i = 0;
	file->map_y = 0;
	while (node)
	{
		check_line(node, infos, file);
		if (!(infos->map[i] = malloc(sizeof(char) * (file->map_width + 1))))
			ft_map_error(infos, node, "Malloc failed in parsing.");
		format_line(infos->map[i++], node->content);
		file->line++;
		file->column = 0;
		file->map_y++;
		tmp = node;
		node = node->next;
		free(tmp->content);
		free(tmp);
	}
	infos->map[i] = 0;
}

void	format_line(char *dest, char *src)
{
	while (*src)
	{
		if (*src != ' ')
			*dest++ = *src;
		src++;
	}
	*dest = 0;
}
