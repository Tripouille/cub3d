/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_resolution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:06:44 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:06:45 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_resolution(t_file *file, __attribute__((unused))
						t_infos *infos, __attribute__((unused)) char *id)
{
	if (g_win_w != -1)
		ft_error(infos, "Line %i : Resolution has already been set.",
		file->line);
	set_resolution_width(infos, file);
	skip_spaces(infos, file, REQUIRED);
	set_resolution_height(infos, file);
}

void	set_resolution_width(t_infos *infos, t_file *file)
{
	if (*file->buffer == '\n')
		ft_error(infos, "Missing width resolution.");
	g_win_w = get_number(file);
	if (g_win_w == 0)
		ft_error(infos, "Width resolution is invalid.");
	else if (g_win_w > MAX_RESOLUTION_WIDTH)
	{
		ft_warning("Line %i : width resolution can't be higher than %i.",
					file->line, MAX_RESOLUTION_WIDTH);
		ft_dprintf(2, "%sResizing to screen width. %lc\n%s",
					GREEN, OK_SMILEY, RESET);
		g_win_w = MAX_RESOLUTION_WIDTH;
	}
	else if (g_win_w < MIN_RESOLUTION_WIDTH)
	{
		ft_warning("Line %i : width resolution is too small.", file->line);
		ft_dprintf(2, "%sResizing to %i. %lc\n%s",
					GREEN, MIN_RESOLUTION_WIDTH, OK_SMILEY, RESET);
		g_win_w = MIN_RESOLUTION_WIDTH;
	}
}

void	set_resolution_height(t_infos *infos, t_file *file)
{
	if (*file->buffer == '\n')
		ft_error(infos, "Missing height resolution.");
	g_win_h = get_number(file);
	if (g_win_h == 0)
		ft_error(infos, "Height resolution is invalid.");
	else if (g_win_h > MAX_RESOLUTION_HEIGHT)
	{
		ft_warning("Line %i : height resolution can't be higher than %i.",
					file->line, MAX_RESOLUTION_HEIGHT);
		ft_dprintf(2, "%sResizing to screen height. %lc\n%s",
					GREEN, OK_SMILEY, RESET);
		g_win_h = MAX_RESOLUTION_HEIGHT;
	}
	else if (g_win_h < MIN_RESOLUTION_HEIGHT)
	{
		ft_warning("Line %i : height resolution is too small.", file->line);
		ft_dprintf(2, "%sResizing to %i. %lc\n%s",
					GREEN, MIN_RESOLUTION_HEIGHT, OK_SMILEY, RESET);
		g_win_h = MIN_RESOLUTION_HEIGHT;
	}
}
