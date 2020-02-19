/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:02:35 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:02:36 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Bitmap header size, width of image, height of image (negative to write from
** top to bottom), reserved field, number of bits per pixel, compression,
** image size, resolution, color information.
*/

void	bmp_fill_bitmap_header(char *bitmap)
{
	*((int*)(bitmap + 14)) = 40;
	*((int*)(bitmap + 18)) = g_win_w;
	*((int*)(bitmap + 22)) = -g_win_h;
	bitmap[26] = 1;
	bitmap[27] = 0;
	bitmap[28] = 32;
	bitmap[29] = 0;
	*((int*)(bitmap + 30)) = 0;
	*((int*)(bitmap + 34)) = g_win_h * g_win_w * 4;
	*((int*)(bitmap + 38)) = 2835;
	*((int*)(bitmap + 42)) = 2835;
	*((int*)(bitmap + 46)) = 0;
	*((int*)(bitmap + 50)) = 0;
}

/*
** Bitmap signature, file size, reserved field, header size.
*/

void	bmp_fill_file_header(char *bitmap)
{
	bitmap[0] = 'B';
	bitmap[1] = 'M';
	*((int*)(bitmap + 2)) = BMP_HEADER_SIZE + g_win_h * g_win_w * 4;
	*((int*)(bitmap + 6)) = 0;
	*((int*)(bitmap + 10)) = BMP_HEADER_SIZE;
}

void	make_bmp(t_infos *infos)
{
	int		fd;
	char	bitmap[BMP_HEADER_SIZE];

	bmp_fill_file_header(bitmap);
	bmp_fill_bitmap_header(bitmap);
	fd = open("save.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	write(fd, bitmap, BMP_HEADER_SIZE);
	write(fd, infos->data, g_win_h * g_win_w * 4);
	close(fd);
}
