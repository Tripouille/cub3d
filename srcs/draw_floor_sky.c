/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_sky.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:03:46 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/16 12:20:46 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sky_color(t_infos *infos, int screen_x, int sky_end)
{
	int		y;

	y = 0;
	while (y < sky_end)
		infos->data[y++ * g_win_w + screen_x] = infos->sky_color;
}

void	draw_sky_texture(t_infos *infos, int screen_x, int sky_end)
{
	int		screen_y;
	double	texture_y;
	double	r;
	double	pixel_per_deg;
	int		texture_x;

	r = (double)infos->texture[SKY_TEXT].h / g_win_h;
	pixel_per_deg = infos->texture[SKY_TEXT].w / 360.0;
	texture_x = (((double)screen_x / g_win_w) * FOV) * pixel_per_deg
				- (true_angle(infos->player.angle + (FOV / 2)) * pixel_per_deg);
	texture_x = infos->texture[SKY_TEXT].w + texture_x;
	texture_y = infos->player.thickness
				+ infos->player.z + infos->player.angle_z;
	screen_y = -1;
	while (++screen_y < sky_end)
		infos->data[screen_y * g_win_w + screen_x] =
		infos->texture[SKY_TEXT].data[(int)(texture_y++ * r)
		* infos->texture[SKY_TEXT].w + texture_x];
}

int		get_floor_color(int original_color, int dist)
{
	int		color;
	double	color_r;

	color_r = dist / (g_win_h / 2.0) * LIGHT_RATIO;
	if (color_r > 1.0)
		color_r = 1.0;
	color = (original_color % 0x000100) * color_r;
	color += (int)((((original_color / 0x000100) % 0x000100) * color_r))
	* 0x000100;
	color += (int)((((original_color / 0x010000) % 0x000100) * color_r))
	* 0x010000;
	return (color);
}

void	draw_floor_color(t_infos *infos, int screen_x, int y)
{
	while (y < g_win_h)
	{
		infos->data[y * g_win_w + screen_x] =
			get_floor_color(infos->floor_color, y - g_win_h / 2
			+ infos->player.z + infos->player.angle_z);
		y++;
	}
}

void	draw_floor_texture(t_infos *infos, int x, double angle, int y)
{
	double		world_dist;
	t_coord		world;
	t_coord		text;
	double		trigo[2];

	trigo[0] = sin(angle * (M_PI / 180.0));
	trigo[1] = cos(angle * (M_PI / 180.0));
	while (y < g_win_h)
	{
		world_dist = infos->wall_height_at_dist_1 / (g_win_h -
				(g_win_h - (y + infos->player.z + infos->player.angle_z)) * 2);
		world.y = infos->player.y - world_dist * trigo[0];
		world.y = world.y < 0 ? 0 : world.y;
		world.x = infos->player.x + world_dist * trigo[1];
		world.x = world.x < 0 ? 0 : world.x;
		text.x = (world.x % g_win_h) / (double)g_win_h
					* infos->texture[FLOOR_TEXT].w;
		text.y = (world.y % g_win_h) / (double)g_win_h
					* infos->texture[FLOOR_TEXT].h;
		infos->data[y * g_win_w + x] =
			get_floor_color(infos->texture[FLOOR_TEXT].data[text.y
					* infos->texture[FLOOR_TEXT].w + text.x], y - g_win_h / 2
									+ infos->player.z + infos->player.angle_z);
		y++;
	}
}
