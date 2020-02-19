/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:04:57 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:04:59 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long	timediff(t_timespec old, t_timespec new)
{
	return ((new.tv_sec - old.tv_sec) * 1E9 + (new.tv_nsec - old.tv_nsec));
}

void	free_lists(t_infos *infos)
{
	void		*tmp;

	while (infos->sprite_list)
	{
		tmp = infos->sprite_list;
		infos->sprite_list = infos->sprite_list->next;
		free(tmp);
	}
	infos->sprite_list = 0;
	while (infos->door_list)
	{
		tmp = infos->door_list;
		infos->door_list = infos->door_list->next;
		free(tmp);
	}
	infos->door_list = 0;
}

void	free_all(t_infos *infos)
{
	int			i;

	system("pkill -f afplay");
	i = 0;
	while (infos->map && infos->map[i])
	{
		free(infos->map[i]);
		i++;
	}
	free(infos->map);
	infos->map = 0;
	free_lists(infos);
	if (infos->img)
		mlx_destroy_image(infos->mlx, infos->img);
	if (infos->win)
		mlx_destroy_window(infos->mlx, infos->win);
}

/*
** Return an angle between (0 - 360) ex -1 -> 359.
*/

double	true_angle(double nb)
{
	double	result;

	return ((result = fmod(nb, 360.0)) < 0.0 ? result + 360.0 : result);
}

int		ft_exit(t_infos *infos)
{
	free_all(infos);
	system("pkill -f afplay");
	exit(EXIT_SUCCESS);
}
