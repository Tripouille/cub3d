/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:06:56 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/16 12:24:16 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_texture(t_file *file, t_infos *infos, char *id)
{
	void		*img;
	char		filename[100];
	int			len;
	int			text_id;

	text_id = get_texture_id(id);
	if (infos->texture[text_id].data || (*id == 'C' && infos->sky_color != -1)
	|| (*id == 'F' && infos->floor_color != -1))
		ft_error(infos, "Line %i : %s : already set.", file->line, id);
	len = 0;
	while (*file->buffer)
		filename[len++] = *file->buffer++;
	filename[len] = 0;
	if (!path_is_valid(filename, ".xpm"))
		ft_error(infos, "Line %i : %s : \
%s extension is invalid, should be .xpm.", file->line, id, filename);
	if (!(img = mlx_xpm_file_to_image(infos->mlx, filename,
	&(infos->texture[text_id].w), &(infos->texture[text_id].h))))
		ft_error(infos, "Line %i : %s : file %s not found.",
		file->line, id, filename);
	infos->texture[text_id].data = (int*)mlx_get_data_addr(img,
	&(infos->bits_per_pixel), &(infos->size_line), &(infos->endian));
	if (text_id == SPR_TEXT)
		set_texture_ratios(infos->texture + text_id);
}

int		get_texture_id(char *id)
{
	if (!ft_strcmp(id, "NO"))
		return (N_TEXT);
	if (!ft_strcmp(id, "SO"))
		return (S_TEXT);
	if (!ft_strcmp(id, "WE"))
		return (W_TEXT);
	if (!ft_strcmp(id, "EA"))
		return (E_TEXT);
	if (!ft_strcmp(id, "C"))
		return (SKY_TEXT);
	if (!ft_strcmp(id, "F"))
		return (FLOOR_TEXT);
	return (SPR_TEXT);
}

/*
** Sets the width ratio to the first and the last
** non transparent columns of the texture.
*/

void	set_texture_ratios(t_texture *texture)
{
	int		x;
	int		y;

	x = -1;
	y = texture->h;
	while (y == texture->h && ++x < texture->w)
	{
		y = 0;
		while (y < texture->h
		&& texture->data[y * texture->w + x] == texture->data[0])
			y++;
	}
	texture->start_r = (double)x / texture->w;
	y = -1;
	while (y < texture->h && ++x < texture->w)
	{
		y = 0;
		while (y < texture->h
		&& texture->data[y * texture->w + x] == texture->data[0])
			y++;
	}
	texture->end_r = (double)x / texture->w;
}
