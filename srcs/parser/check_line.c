/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:05:36 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:43:15 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_line(t_list *node, t_infos *infos, t_file *file)
{
	if (file->map_y == 0)
	{
		if ((file->map_width = check_border(infos, node, file)) < 3)
			ft_map_error(infos, node, "Map is too small.");
	}
	else if (!node->next)
	{
		if (file->map_width != check_border(infos, node, file))
			ft_map_error(infos, node,
			"Line %i (last) : its length is different from the others.",
			file->line);
	}
	else if (file->map_width != check_middle(node, file, infos))
		ft_map_error(infos, node,
		"Line %i : its length is different from the others.", file->line);
}

int		check_border(t_infos *infos, t_list *node, t_file *file)
{
	int		length;
	char	*line;

	line = node->content;
	length = 0;
	file->column = 0;
	while (line[file->column])
	{
		if (line[file->column] == WALL)
			length++;
		else if (line[file->column] != ' ')
			ft_map_error(infos, node, "Line %i, column %i : should be a wall.",
			file->line, file->column + 1);
		file->column++;
	}
	return (length);
}

int		check_middle(t_list *node, t_file *file, t_infos *infos)
{
	char	*line;

	line = node->content;
	remove_end_spaces(line);
	file->column = 0;
	skip_map_spaces(line, &(file->column));
	if (line[file->column] != WALL)
		ft_map_error(infos, node,
		"Line %i, column %i : does not start with a wall.",
		file->line, file->column + 1);
	file->column++;
	file->map_x = 1;
	skip_map_spaces(line, &(file->column));
	while (line[file->column] && line[file->column + 1])
	{
		check_character(line[file->column], infos, file, node);
		file->map_x++;
		file->column++;
		skip_map_spaces(line, &(file->column));
	}
	if (line[file->column] != WALL)
		ft_map_error(infos, node,
		"Line %i, column %i : does not end with a wall.",
		file->line, file->column + 1);
	return (file->map_x + 1);
}

void	check_character(char c, t_infos *infos, t_file *file, t_list *node)
{
	if (c == 'E' || c == 'N' || c == 'W' || c == 'S')
	{
		if (infos->player.angle != -1.0)
			ft_map_error(infos, node,
			"Line %i, column %i : player is placed a second time.",
			file->line, file->column + 1);
		infos->player.angle = get_angle(c);
		infos->player.y = file->map_y * g_win_h + g_win_h / 2.0;
		infos->player.x = file->map_x * g_win_h + g_win_h / 2.0;
	}
	else if (c >= SPRITE && c <= SPRITE2_BIG)
		add_sprite(infos, c - SPRITE, file, node);
	else if (c == DOOR)
		add_door(infos, file, node);
	else if (c != EMPTY && c != WALL)
		ft_map_error(infos, node,
		"Line %i, column %i : invalid character in map.",
		file->line, file->column + 1);
}

double	get_angle(char c)
{
	if (c == 'E')
		return (EAST + 0.01);
	else if (c == 'N')
		return (NORTH);
	else if (c == 'W')
		return (WEST);
	else if (c == 'S')
		return (SOUTH);
	return (-1);
}
