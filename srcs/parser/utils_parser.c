/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:07:56 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:07:57 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		path_is_valid(char *path, char *extension)
{
	int		extension_size;
	int		path_size;

	extension_size = ft_strlen(extension);
	path_size = ft_strlen(path);
	if (!path_size)
		return (0);
	while (path[--path_size] == ' ')
		;
	path[++path_size] = 0;
	if (path_size < extension_size)
		return (0);
	return (!ft_strcmp(extension, path + path_size - extension_size));
}

int		get_number(t_file *file)
{
	long	number;

	number = 0;
	while (ft_isdigit(*file->buffer) && number < INT_MAX)
	{
		number = number * 10 + *file->buffer++ - '0';
		file->column++;
	}
	if (number > INT_MAX)
		while (ft_isdigit(*file->buffer))
		{
			file->buffer++;
			file->column++;
		}
	return (number < INT_MAX ? number : INT_MAX);
}

int		idcmp(t_file *file, char *id)
{
	int		i;

	i = 0;
	while (id[i] && file->buffer[i] == id[i])
		i++;
	if (!id[i])
	{
		file->buffer += i;
		file->column += i;
	}
	return (id[i]);
}
