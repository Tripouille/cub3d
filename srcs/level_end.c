/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:04:22 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 13:28:43 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		next_level(t_infos *infos)
{
	char		map_name[14];

	if (infos->map_level == LEVEL_ONE && access(BOSS_MAP_NAME, F_OK) != -1)
	{
		ft_strlcpy(map_name, BOSS_MAP_NAME, ft_strlen(BOSS_MAP_NAME) + 1);
		free_all(infos);
		initializer(infos, map_name);
		infos->map_level = LAST_LEVEL;
	}
	else
		game_over(infos);
}

int			ennemies_alive(t_sprite *sprite)
{
	while (sprite)
	{
		if (sprite->type >= 1)
			return (1);
		sprite = sprite->next;
	}
	return (0);
}

void		sprite_dies(t_infos *infos)
{
	system("afplay -q 1 -v 2 sounds/yeti_die.mp3&");
	if (!ennemies_alive(infos->sprite_list))
		next_level(infos);
}

void		game_over(t_infos *infos)
{
	int		x;
	int		y;
	double	r_x;
	double	r_y;

	infos->game_over = 1;
	draw_threads(infos);
	r_x = (double)infos->texture[GAME_OVER_TEXT].w / g_win_w;
	r_y = (double)infos->texture[GAME_OVER_TEXT].h / g_win_h;
	x = -1;
	while (++x < g_win_w)
	{
		y = -1;
		while (++y < g_win_h)
			infos->data[y * g_win_w + x] =
				infos->texture[GAME_OVER_TEXT].data[(int)(y * r_y)
				* infos->texture[GAME_OVER_TEXT].w + (int)(x * r_x)]
				+ 0x40000000;
	}
	mlx_put_image_to_window(infos->mlx, infos->win, infos->img, 0, 0);
}

void		kill_them_all(t_infos *infos)
{
	int				x;
	int				y;
	double			r_x;
	double			r_y;
	int				actual_pixel;

	if ((infos->kta_alph += infos->elapsed_time * 1E9 / ((KTA_CD) / 255))
	>= 254.0)
		return ;
	mlx_put_image_to_window(infos->mlx, infos->win, infos->img, 0, 0);
	r_x = (double)infos->texture[KTA_TEXT].w / g_win_w;
	r_y = (double)infos->texture[KTA_TEXT].h / g_win_h;
	x = -1;
	while (++x < g_win_w)
	{
		y = -1;
		while (++y < g_win_h)
		{
			actual_pixel = infos->texture[KTA_TEXT].data[(int)(y * r_y)
								* infos->texture[KTA_TEXT].w + (int)(x * r_x)];
			if (actual_pixel != infos->texture[KTA_TEXT].data[0])
				infos->data[y * g_win_w + x] = actual_pixel
											+ (int)infos->kta_alph * 0x01000000;
		}
	}
}
