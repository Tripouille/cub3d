/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:03:35 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/16 15:22:59 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fps(void)
{
	static t_timespec	old = {0, 0};
	t_timespec			new;
	static int			fps = 0;

	fps++;
	if (!old.tv_sec)
		clock_gettime(CLOCK_REALTIME, &old);
	clock_gettime(CLOCK_REALTIME, &new);
	if (timediff(old, new) > 1E9)
	{
		ft_printf("FPS [%.2f]\n", (double)fps / (timediff(old, new) / 1E9));
		fps = 0;
		clock_gettime(CLOCK_REALTIME, &old);
	}
}

void	draw(t_infos *infos, int x)
{
	double			angle;
	double			wall_dist;

	angle = true_angle(infos->player.angle + FOV / 2.0
						- FOV * (x / (double)g_win_w));
	infos->wall_height_at_dist_1 =
	g_win_h * g_win_h / cos((infos->player.angle - angle) * (M_PI / 180.0));
	wall_dist = raycast(infos, &(infos->player), angle);
	infos->wall_size = infos->wall_height_at_dist_1 / wall_dist;
	draw_column(infos, x, angle, g_win_h / 2 + infos->wall_size / 2
								- infos->player.z - infos->player.angle_z);
	draw_sprites(infos, angle, wall_dist, x);
}

void	*predraw(void *thread)
{
	static pthread_mutex_t		m = PTHREAD_MUTEX_INITIALIZER;
	int							x;

	while (*(((t_thread*)thread)->x) < g_win_w)
	{
		pthread_mutex_lock(&m);
		++*(((t_thread*)thread)->x);
		x = *(((t_thread*)thread)->x);
		pthread_mutex_unlock(&m);
		if (x < g_win_w)
			draw(&(((t_thread*)thread)->infos), x);
	}
	return (0);
}

void	initialize_threads(t_thread *thread, t_infos *infos, int *t_x)
{
	int		i;

	i = -1;
	while (++i < 5)
	{
		thread[i].infos = *infos;
		thread[i].x = t_x;
	}
}

/*
** Draws on the entire screen with draw function.
** Calculates general infos for sprites, then draws by columns by threads,
** then sprite health bars, hud and eventually the "kill them all" screen.
*/

void	draw_threads(t_infos *infos)
{
	t_thread		thread[5];
	int				t_x;
	int				i;

	fps();
	calculate_sprite_infos(infos);
	sort_sprites(&(infos->sprite_list), sprite_lst_size(infos->sprite_list));
	t_x = -1;
	initialize_threads(thread, infos, &t_x);
	i = -1;
	while (++i < 5)
		pthread_create(&(thread[i].id), NULL, predraw, thread + i);
	pthread_join(thread[0].id, NULL);
	pthread_join(thread[1].id, NULL);
	pthread_join(thread[2].id, NULL);
	pthread_join(thread[3].id, NULL);
	pthread_join(thread[4].id, NULL);
	draw_sprites_life(infos, infos->sprite_list);
	draw_hud(infos);
	if (infos->kta_alph < 254.0)
		kill_them_all(infos);
	mlx_put_image_to_window(infos->mlx, infos->win, infos->img, 0, 0);
}
