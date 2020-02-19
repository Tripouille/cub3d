/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 11:09:36 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/16 13:51:13 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct timespec		t_timespec;

typedef struct	s_ratio
{
	double			x;
	double			y;
}				t_ratio;

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef struct	s_object
{
	double		x;
	double		y;
	double		z;
	double		angle_z;
	double		angle;
	double		v_angle;
	double		speed;
	double		thickness;
	double		hp;
}				t_object;

typedef struct	s_door
{
	t_coord			pos;
	double			gap;
	int				status;
	struct s_door	*next;
}				t_door;

typedef struct	s_sprite
{
	int				type;
	t_object		object;
	int				start_x;
	int				end_x;
	int				start_y;
	int				middle_end_y;
	double			start_ang;
	double			end_ang;
	double			center_ang;
	double			ang_size;
	double			ratio;
	double			dist;
	double			height;
	double			size_mult;
	double			damage;
	t_timespec		attack_time;
	t_timespec		move_time;
	int				frame;
	int				already_attacked;
	int				active;
	double			last_move;
	struct s_sprite	*next;
}				t_sprite;

typedef struct	s_ray_infos
{
	double		v_dist;
	double		h_dist;
	int			dir;
	double		cos_angle;
	double		sin_angle;
}				t_ray_infos;

typedef struct	s_texture
{
	int			*data;
	int			w;
	int			h;
	double		start_r;
	double		end_r;
}				t_texture;

typedef struct	s_hud
{
	int			*data;
	int			w;
	int			h;
	double		start_x;
	double		end_x;
	double		start_y;
	double		end_y;
}				t_hud;

typedef struct	s_key
{
	char	w;
	char	s;
	char	a;
	char	d;
	char	left;
	char	right;
	char	up;
	char	down;
	char	e;
	char	shift;
	char	space;
}				t_key;

typedef struct	s_infos
{
	void		*mlx;
	void		*win;

	void		*img;
	int			*data;
	int			bits_per_pixel;
	int			size_line;
	int			endian;

	char		**map;
	t_texture	texture[16];
	t_hud		hud[14];
	int			weapon;
	int			weapon_frame;
	int			floor_color;
	int			sky_color;

	t_object	player;
	t_sprite	*sprite_list;
	t_door		*door_list;

	t_coord		box;
	char		box_val;
	int			wall_size;
	double		wall_height_at_dist_1;
	int			wall_start;
	int			wall_o;

	t_key		key;

	int			map_level;
	int			game_over;

	double		kta_alph;
	double		elapsed_time;
	t_timespec	melee_time;
	t_timespec	gun_time;
	t_timespec	heal_time;
	int			already_attacked;
}				t_infos;

typedef struct	s_thread
{
	t_infos		infos;
	pthread_t	id;
	int			*x;
}				t_thread;

typedef struct	s_file
{
	int			fd;
	char		*buffer;
	int			column;
	int			line;
	int			map_width;
	int			map_x;
	int			map_y;
}				t_file;

typedef void	(*t_fct)(t_file *file, __attribute__((unused))
				t_infos *infos, __attribute__((unused)) char *id);

typedef struct	s_option
{
	char		*id;
	t_fct		fct;
}				t_option;

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

#endif
