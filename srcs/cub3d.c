/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:02:50 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/16 14:28:15 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		g_win_w;
int		g_win_h;

void	initialize_times(t_infos *infos)
{
	infos->melee_time.tv_sec = 0;
	infos->gun_time.tv_sec = 0;
	infos->heal_time.tv_sec = 0;
}

void	initialize_player(t_infos *infos)
{
	infos->player.speed = g_win_h * PLAYER_SPEED;
	infos->player.thickness = g_win_h * PLAYER_THICKNESS;
	infos->player.z = 0;
	infos->player.v_angle = 0.0;
	infos->player.angle_z = 0.0;
	infos->player.hp = 1.0;
	infos->already_attacked = 0;
}

void	initializer(t_infos *infos, char *map_name)
{
	initialize_textures(infos);
	parser(infos, map_name);
	if (!(infos->win = mlx_new_window(infos->mlx, g_win_w, g_win_h, "cub3D")))
		ft_error(infos, "mlx_new_window failed.");
	if (!(infos->img = mlx_new_image(infos->mlx, g_win_w, g_win_h)))
		ft_error(infos, "mlx_new_image failed");
	infos->data = (int*)mlx_get_data_addr(infos->img, &(infos->bits_per_pixel),
					&(infos->size_line), &(infos->endian));
	initialize_keys(infos);
	initialize_times(infos);
	initialize_player(infos);
	infos->weapon = MELEE;
	infos->weapon_frame = WEAPON1_TEXT;
	infos->game_over = 0;
	infos->kta_alph = 0.0;
	mlx_hook(infos->win, 2, 0, &key_press, infos);
	mlx_hook(infos->win, 3, 0, &key_release, infos);
	mlx_hook(infos->win, RED_CROSS, 0, &ft_exit, infos);
	mlx_loop_hook(infos->mlx, &tick_event, infos);
	system("while true; do afplay -q 1 -v 5 sounds/ambiance.mp3; done&");
}

void	initialize_infos(t_infos *infos)
{
	infos->mlx = 0;
	infos->win = 0;
	infos->img = 0;
	infos->map = 0;
	infos->sprite_list = 0;
	infos->door_list = 0;
}

int		main(int ac, char **av)
{
	t_infos		infos;

	initialize_infos(&infos);
	if (ac == 1)
		ft_error(&infos, "Need a parameter.");
	else if (ac > 3)
		ft_error(&infos, "Too many parameters.");
	else if (ac == 3 && ft_strcmp(av[2], "--save"))
		ft_error(&infos, "Unknown parameter.");
	if (!(infos.mlx = mlx_init()))
		ft_error(&infos, "mlx_init failed.");
	infos.map_level = LEVEL_ONE;
	initializer(&infos, av[1]);
	mlx_mouse_hide();
	if (ac == 3 && !ft_strcmp(av[2], "--save"))
	{
		draw_threads(&infos);
		make_bmp(&infos);
	}
	else
		mlx_loop(infos.mlx);
	return (EXIT_SUCCESS);
}
