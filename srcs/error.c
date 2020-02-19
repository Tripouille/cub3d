/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:04:08 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:04:08 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_warning(char *msg, ...)
{
	va_list va;
	int		i;
	int		j;
	char	*etc[5];

	va_start(va, msg);
	i = -1;
	j = 0;
	while (msg[++i])
		if (msg[i] == '%')
			etc[j++] = va_arg(va, char *);
	va_end(va);
	write(2, YELLOW, ft_strlen(YELLOW));
	write(2, "Warning\n", 8);
	ft_dprintf(2, msg, etc[0], etc[1], etc[2], etc[3], etc[4]);
	write(2, RESET, ft_strlen(RESET));
	ft_dprintf(2, " %lc\n", WARNING_SMILEY);
}

void	ft_error(t_infos *infos, char *msg, ...)
{
	va_list va;
	int		i;
	int		j;
	char	*etc[5];

	va_start(va, msg);
	i = -1;
	j = 0;
	while (msg[++i])
		if (msg[i] == '%')
			etc[j++] = va_arg(va, char *);
	va_end(va);
	write(2, RED, ft_strlen(RED));
	write(2, "Error\n", 6);
	ft_dprintf(2, msg, etc[0], etc[1], etc[2], etc[3], etc[4]);
	write(2, RESET, ft_strlen(RESET));
	ft_dprintf(2, " %lc\n", ERROR_SMILEY);
	free_all(infos);
	exit(EXIT_FAILURE);
}

void	ft_map_error(t_infos *infos, t_list *head, char *msg, ...)
{
	va_list va;
	int		i;
	int		j;
	char	*etc[5];

	va_start(va, msg);
	i = -1;
	j = 0;
	while (msg[++i])
		if (msg[i] == '%')
			etc[j++] = va_arg(va, char *);
	va_end(va);
	write(2, RED, ft_strlen(RED));
	write(2, "Error\n", 6);
	ft_dprintf(2, msg, etc[0], etc[1], etc[2], etc[3], etc[4]);
	write(2, RESET, ft_strlen(RESET));
	ft_dprintf(2, " %lc\n", ERROR_SMILEY);
	lst_purge(head);
	free_all(infos);
	exit(EXIT_FAILURE);
}
