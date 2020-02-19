/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:04:11 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/16 12:26:40 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_own_hud_texture(t_infos *infos, char *filename, t_hud *hud)
{
	void		*img;
	t_coord		dim;

	if (!(img = mlx_xpm_file_to_image(infos->mlx, filename, &dim.x, &dim.y)))
		ft_error(infos, "File %s not found.", filename);
	hud->data = (int*)mlx_get_data_addr(img,
	&(infos->bits_per_pixel), &(infos->size_line), &(infos->endian));
	hud->w = dim.x;
	hud->h = dim.y;
}

void	set_own_texture(t_infos *infos, char *filename, t_texture *texture)
{
	void		*img;
	t_coord		dim;

	if (!(img = mlx_xpm_file_to_image(infos->mlx, filename, &dim.x, &dim.y)))
		ft_error(infos, "File %s not found.", filename);
	texture->data = (int*)mlx_get_data_addr(img,
	&(infos->bits_per_pixel), &(infos->size_line), &(infos->endian));
	texture->w = dim.x;
	texture->h = dim.y;
}

void	initialize_keys(t_infos *infos)
{
	infos->key.w = 0;
	infos->key.s = 0;
	infos->key.a = 0;
	infos->key.d = 0;
	infos->key.left = 0;
	infos->key.right = 0;
	infos->key.up = 0;
	infos->key.down = 0;
	infos->key.e = 0;
	infos->key.shift = 0;
	infos->key.space = 0;
}

void	initialize_textures2(t_infos *infos)
{
	set_own_hud_texture(infos, "textures/hud/inventory_slot1.xpm",
							infos->hud + INVENTORY_SLOT1_TEXT);
	set_own_hud_texture(infos, "textures/hud/inventory_slot2.xpm",
							infos->hud + INVENTORY_SLOT2_TEXT);
	set_own_hud_texture(infos, "textures/hud/inventory_slot3.xpm",
							infos->hud + INVENTORY_SLOT3_TEXT);
	set_own_hud_texture(infos, "textures/hud/hp.xpm", infos->hud + HP_TEXT);
	set_hud_limits(infos->hud + HP_TEXT);
	set_own_hud_texture(infos, "textures/hud/enemy_hp.xpm",
							infos->hud + ENEMY_HP_TEXT);
	set_hud_limits(infos->hud + ENEMY_HP_TEXT);
	set_own_hud_texture(infos, "textures/hud/boss_hp.xpm",
							infos->hud + BOSS_HP_TEXT);
	set_hud_limits(infos->hud + BOSS_HP_TEXT);
	set_own_hud_texture(infos, "textures/hud/weapon1.xpm",
							infos->hud + WEAPON1_TEXT);
	set_own_hud_texture(infos, "textures/hud/weapon2.xpm",
							infos->hud + WEAPON2_TEXT);
	set_own_hud_texture(infos, "textures/hud/weapon3.xpm",
							infos->hud + WEAPON3_TEXT);
	set_own_hud_texture(infos, "textures/hud/gun1.xpm", infos->hud + GUN1_TEXT);
	set_own_hud_texture(infos, "textures/hud/gun2.xpm", infos->hud + GUN2_TEXT);
	set_own_hud_texture(infos, "textures/hud/gun3.xpm", infos->hud + GUN3_TEXT);
	set_own_hud_texture(infos, "textures/hud/gun4.xpm", infos->hud + GUN4_TEXT);
	set_own_hud_texture(infos, "textures/hud/ch.xpm", infos->hud + CH_TEXT);
}

void	initialize_textures(t_infos *infos)
{
	set_own_texture(infos, "textures/door.xpm",
						infos->texture + DOOR_TEXT);
	set_own_texture(infos, "textures/yeti.xpm",
						infos->texture + SPR2_TEXT);
	set_texture_ratios(infos->texture + SPR2_TEXT);
	set_own_texture(infos, "textures/yeti_attack.xpm",
						infos->texture + SPR2_ATTACK_TEXT);
	set_texture_ratios(infos->texture + SPR2_ATTACK_TEXT);
	set_own_texture(infos, "textures/yeti_move1.xpm",
						infos->texture + SPR2_MOVE1_TEXT);
	set_texture_ratios(infos->texture + SPR2_MOVE1_TEXT);
	set_own_texture(infos, "textures/yeti_move2.xpm",
						infos->texture + SPR2_MOVE2_TEXT);
	set_texture_ratios(infos->texture + SPR2_MOVE2_TEXT);
	set_own_texture(infos, "textures/yeti_move3.xpm",
						infos->texture + SPR2_MOVE3_TEXT);
	set_texture_ratios(infos->texture + SPR2_MOVE3_TEXT);
	set_own_texture(infos, "textures/yeti_move4.xpm",
						infos->texture + SPR2_MOVE4_TEXT);
	set_texture_ratios(infos->texture + SPR2_MOVE4_TEXT);
	set_own_texture(infos, "textures/gameover.xpm",
						infos->texture + GAME_OVER_TEXT);
	set_own_texture(infos, "textures/kta.xpm",
						infos->texture + KTA_TEXT);
	initialize_textures2(infos);
}
