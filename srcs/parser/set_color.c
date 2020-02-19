/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:06:25 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:06:39 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		calculate_color(t_infos *infos, t_file *file, char *id)
{
	int		color;
	int		mult;
	int		c;

	color = 0;
	mult = 16 * 16 * 16 * 16;
	while (mult)
	{
		if (!ft_isdigit(*file->buffer))
			ft_error(infos, "Line %i : %c : \
invalid color (not a digit) at column %i.", file->line, *id, file->column);
		c = get_number(file);
		if (c > 255)
			ft_error(infos, "Line %i : %c : \
invalid color (> 255) before column %i", file->line, *id, file->column);
		color += c * mult;
		skip_spaces(infos, file, NOT_REQUIRED);
		if (mult > 1 && *file->buffer++ != ',')
			ft_error(infos, "Line %i : %c : missing comma at column %i.",
						file->line, *id, file->column);
		file->column += mult > 1 ? 1 : 0;
		skip_spaces(infos, file, NOT_REQUIRED);
		mult /= 16 * 16;
	}
	return (color);
}

void	set_color(t_file *file, t_infos *infos, char *id)
{
	int		*color;

	color = *id == 'F' ? &(infos->floor_color) : &(infos->sky_color);
	if (*color != -1 || (*id == 'C' && infos->texture[SKY_TEXT].data)
	|| (*id == 'F' && infos->texture[FLOOR_TEXT].data))
		ft_error(infos, "Line %i : %c color has already been set.",
		file->line, *id);
	*color = calculate_color(infos, file, id);
}

void	switch_color_texture(t_file *file, t_infos *infos, char *id)
{
	if (!ft_isdigit(*file->buffer) || path_is_valid(file->buffer, ".xpm"))
		set_texture(file, infos, id);
	else
		set_color(file, infos, id);
}
