/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:05:44 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/16 12:23:45 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_option(t_option *option, char *id, t_fct fct)
{
	option->id = id;
	option->fct = fct;
}

void	init_options(t_option *options)
{
	init_option(options, "R", &set_resolution);
	init_option(options + 1, "NO", &set_texture);
	init_option(options + 2, "SO", &set_texture);
	init_option(options + 3, "WE", &set_texture);
	init_option(options + 4, "EA", &set_texture);
	init_option(options + 5, "S", &set_texture);
	init_option(options + 6, "F", &switch_color_texture);
	init_option(options + 7, "C", &switch_color_texture);
	init_option(options + 8, 0, 0);
}
