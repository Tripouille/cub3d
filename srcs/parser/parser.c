/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:06:10 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/16 13:36:29 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parser(t_infos *infos, char *path)
{
	t_file		file;
	t_option	options[15];
	char		*buffer_start;

	if (!path_is_valid(path, ".cub"))
		ft_error(infos, "%s extension is invalid, should be .cub.", path);
	if ((file.fd = open(path, O_RDONLY)) < 0)
		ft_error(infos, "open(\"%s\", O_RDONLY) failed.", path);
	init_options(options);
	init_infos(infos);
	file.line = 1;
	file.column = 1;
	parse_options(&file, infos, options, &buffer_start);
	parse_map(&file, infos, buffer_start);
	check_options(infos);
}

void	init_infos(t_infos *infos)
{
	int		i;

	g_win_w = -1;
	g_win_h = -1;
	infos->floor_color = -1;
	infos->sky_color = -1;
	infos->player.angle = -1.0;
	i = -1;
	while (++i < SPR2_TEXT)
		infos->texture[i].data = 0;
	infos->sprite_list = 0;
	infos->door_list = 0;
}

void	parse_options(t_file *file, t_infos *infos, t_option *options,
						char **buffer_start)
{
	int		r;

	if ((r = get_next_line(file->fd, &(file->buffer))) == -1)
		ft_error(infos, "Config file reading failed.");
	*buffer_start = file->buffer;
	skip_spaces(infos, file, NOT_REQUIRED);
	while (r && *file->buffer != WALL)
	{
		if (*file->buffer != '#')
			set_option(options, file, infos);
		file->line++;
		file->column = 1;
		free(*buffer_start);
		if ((r = get_next_line(file->fd, &(file->buffer))) == -1)
			ft_error(infos, "Config file reading failed.");
		*buffer_start = file->buffer;
		skip_spaces(infos, file, NOT_REQUIRED);
	}
}

void	set_option(t_option *options, t_file *file, t_infos *infos)
{
	int		i;

	i = 0;
	while (options[i].id && idcmp(file, options[i].id))
		i++;
	if (options[i].id)
	{
		skip_spaces(infos, file, REQUIRED);
		options[i].fct(file, infos, options[i].id);
	}
	skip_spaces(infos, file, NOT_REQUIRED);
	endofline(infos, file);
}

void	check_options(t_infos *infos)
{
	if (g_win_w == -1 || g_win_h == -1)
		ft_error(infos, "Resolution was not set.");
	else if (!infos->texture[N_TEXT].data)
		ft_error(infos, "Texture for NO was not set.");
	else if (!infos->texture[W_TEXT].data)
		ft_error(infos, "Texture for WE was not set.");
	else if (!infos->texture[S_TEXT].data)
		ft_error(infos, "Texture for SO was not set.");
	else if (!infos->texture[E_TEXT].data)
		ft_error(infos, "Texture for EA was not set.");
	else if (!infos->texture[SPR_TEXT].data)
		ft_error(infos, "Texture for S was not set.");
	else if (infos->floor_color == -1 && !infos->texture[FLOOR_TEXT].data)
		ft_error(infos, "Color for floor was not set.");
	else if (infos->sky_color == -1 && !infos->texture[SKY_TEXT].data)
		ft_error(infos, "Color for sky was not set.");
	else if (infos->player.angle == -1.0)
		ft_error(infos, "Missing player in map.");
}
