/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 11:07:31 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/16 13:16:12 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define BOSS_MAP_NAME "maps/boss.cub"

# define PLAYER_THICKNESS 0.4
# define PLAYER_SPEED 4.0
# define ANGLE_SPEED 180.0
# define Z_ANGLE_SPEED 30.0
# define Z_ANGLE_MAX 30.0
# define FOV 60.0
# define ATTACK_CD 250E6
# define GUN_CD 333E6
# define MELEE_RANGE 1.3
# define MELEE_CH_Y 0.65
# define PLAYER_DAMAGE 0.1
# define HEAL_CD 1E9
# define HEAL 0.05

# define ENEMY_CD 1E9
# define ENEMY_MOVE_CD 0.5E9
# define ENEMY_RANGE 0.5
# define ENEMY_DAMAGE 0.1
# define SPRITE_SPEED 1.5
# define SPRITE_ACTIVATION_RADIUS 5.0

# define MIN_RESOLUTION_WIDTH 100
# define MIN_RESOLUTION_HEIGHT 100
# define MAX_RESOLUTION_WIDTH 2560
# define MAX_RESOLUTION_HEIGHT 1395

# define BIG 2.0
# define STANDARD 0.8
# define SMALL 0.5
# define XSMALL 0.25

# define CLOSED 0
# define OPEN 1
# define DOOR_CD 4.0E9
# define DOOR_RADIUS 2.0

# define LIGHT_RATIO 5.0
# define HP_RATIO 0.25
# define SPRITE_HP_RATIO 0.15
# define WEAPON_RATIO 0.4
# define INVENTORY_RATIO 0.4

# define EAST 0.0
# define NORTH 90.0
# define WEST 180.0
# define SOUTH 270.0

# define LEFT -1.0
# define RIGHT 1.0

# define RESET "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"

# define ERROR_SMILEY 0x1F621
# define WARNING_SMILEY 0x1F631
# define OK_SMILEY 0x1F913

# define RED_CROSS 17
# define BMP_HEADER_SIZE 54

# define KTA_CD 3.0E9

enum	{A_KEY = 0, S_KEY, D_KEY, W_KEY = 13, E_KEY = 14, R_KEY = 15};
enum	{ONE_KEY = 18, TWO_KEY = 19, THREE_KEY = 20, LEFT_KEY = 123};
enum	{RIGHT_KEY = 124, UP_KEY = 126, DOWN_KEY = 125, CTRL_KEY = 256};
enum	{SHIFT_KEY = 257, ESC_KEY = 53, SPACE_KEY = 49};
enum	{EMPTY = '0', WALL = '1', SPRITE = '2', SPRITE2 = '3'};
enum	{SPRITE2_SMALL = '4', SPRITE2_BIG = '5', DOOR = 'D'};

enum	{E_TEXT, N_TEXT, W_TEXT, S_TEXT, SKY_TEXT, FLOOR_TEXT, SPR_TEXT};
enum	{SPR2_TEXT = 7, SPR2_ATTACK_TEXT, GAME_OVER_TEXT, DOOR_TEXT};
enum	{KTA_TEXT = 11, SPR2_MOVE1_TEXT, SPR2_MOVE2_TEXT, SPR2_MOVE3_TEXT};
enum	{SPR2_MOVE4_TEXT = 15, LAST_TEXT};

enum	{HP_TEXT, ENEMY_HP_TEXT, BOSS_HP_TEXT, WEAPON1_TEXT, WEAPON2_TEXT};
enum	{WEAPON3_TEXT = 5, GUN1_TEXT, GUN2_TEXT, GUN3_TEXT, GUN4_TEXT, CH_TEXT};
enum	{INVENTORY_SLOT1_TEXT = 11, INVENTORY_SLOT2_TEXT, INVENTORY_SLOT3_TEXT};
enum	{OEAST, ONORTH, OWEST, OSOUTH, OSPRITE};
enum	{NOT_REQUIRED, REQUIRED};
enum	{MELEE, GUN, POTATO};
enum	{LEVEL_ONE, LAST_LEVEL};

#endif
