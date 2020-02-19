/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:07:04 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:07:05 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_spaces(t_infos *infos, t_file *file, int is_required)
{
	if (is_required && *file->buffer != ' ')
		ft_error(infos, "Missing space at line %i, column %i.",
					file->line, file->column);
	while (*file->buffer == ' ')
	{
		file->buffer++;
		file->column++;
	}
}

void	endofline(t_infos *infos, t_file *file)
{
	if (*file->buffer)
		ft_error(infos, "Invalid character at line %i, column %i.",
					file->line, file->column);
}

void	skip_map_spaces(char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}

void	remove_end_spaces(char *line)
{
	int		i;

	i = 0;
	while (line[i])
		i++;
	while (line[--i] == ' ')
		;
	line[i + 1] = 0;
}
