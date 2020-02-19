/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 10:13:19 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/16 13:15:24 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Draws the floor/sky then the wall on one column.
*/

void	draw_column(t_infos *infos, int screen_x, double angle, int floor_start)
{
	int			screen_y;
	double		r;
	double		color_r;
	t_coord		text_coord;
	t_texture	*text;

	text = infos->texture
			+ (infos->box_val == DOOR ? DOOR_TEXT : infos->wall_o);
	text_coord.x = get_texture_x(infos, text);
	r = (double)text->h / infos->wall_size;
	color_r = infos->wall_size * LIGHT_RATIO / g_win_h;
	if (color_r > 1.0)
		color_r = 1.0;
	infos->wall_start = floor_start - infos->wall_size;
	screen_y = infos->wall_start < 0 ? 0 : infos->wall_start;
	text_coord.y = infos->wall_start < 0 ? -infos->wall_start : 0;
	draw_floor_sky(infos, screen_x, angle, floor_start);
	while (screen_y < g_win_h && text_coord.y < infos->wall_size)
		infos->data[screen_y++ * g_win_w + screen_x] = get_color(text->data
			[(int)(text_coord.y++ * r) * text->w + text_coord.x], color_r);
}

void	draw_floor_sky(t_infos *infos, int screen_x,
						double angle, int floor_start)
{
	if (infos->texture[SKY_TEXT].data)
		draw_sky_texture(infos, screen_x, infos->wall_start);
	else
		draw_sky_color(infos, screen_x, infos->wall_start);
	if (infos->texture[FLOOR_TEXT].data)
		draw_floor_texture(infos, screen_x, angle, floor_start);
	else
		draw_floor_color(infos, screen_x, floor_start);
}

/*
** Gets the pixel from the image to display, using wall size and coordinates.
*/

int		get_color(int original_color, double color_r)
{
	int		color;

	color = (original_color % 0x000100) * color_r;
	color += (int)((((original_color / 0x000100) % 0x000100) * color_r))
	* 0x000100;
	color += (int)((((original_color / 0x010000) % 0x000100) * color_r))
	* 0x010000;
	return (color);
}

int		get_texture_x(t_infos *infos, t_texture *text)
{
	int			x;

	if (infos->wall_o == OEAST
	|| (infos->wall_o == OWEST && infos->box_val == DOOR))
		x = infos->box.y % g_win_h;
	else if (infos->wall_o == ONORTH
	|| (infos->wall_o == OSOUTH && infos->box_val == DOOR))
		x = infos->box.x % g_win_h;
	else if (infos->wall_o == OWEST)
		x = g_win_h - infos->box.y % g_win_h;
	else
		x = g_win_h - infos->box.x % g_win_h;
	x = (double)x / g_win_h * text->w;
	if (infos->box_val == DOOR)
		x -= get_door(infos)->gap * text->w;
	return (x ? x - 1 : 0);
}
