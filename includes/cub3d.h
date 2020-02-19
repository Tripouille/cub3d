/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:27:19 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/16 12:18:03 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <pthread.h>
# include "libft.h"
# include "mlx.h"
# include "define.h"
# include "struct.h"

extern int		g_win_w;
extern int		g_win_h;

void		actualize_speed(t_infos *infos);
void		actualize_angles(t_infos *infos);

void		copy_time(t_timespec *dst, const t_timespec *src);
void		gun_attack_animation(t_infos *infos);
void		attack_animation(t_infos *infos);
void		heal_animation(t_infos *infos);

void		hit(t_infos *infos, t_sprite **sprite_prev,
						t_sprite *sprite, double damage);
void		gun_attack(t_infos *infos, double damage);
void		melee_attack(t_infos *infos, double damage);

void		bmp_fill_bitmap_header(char *bitmap);
void		bmp_fill_file_header(char *bitmap);
void		make_bmp(t_infos *infos);

int			ch_is_on_ennemy(int weapon, t_sprite *sprite);
int			ch_is_on_ennemies(t_infos *infos);
void		draw_crosshair(t_infos *infos);

void		initialize_times(t_infos *infos);
void		initialize_player(t_infos *infos);
void		initializer(t_infos *infos, char *map_name);

int			is_in_sprite_hitbox(t_sprite *sprite, double angle, double radius);
double		min_dist_to_sprite(t_object *obj,
							t_sprite *sprite, double check_angle);
double		min_dist_to_wall(t_infos *infos, t_object *obj,
							double check_angle, int *orientation);
double		walkable_distance(t_infos *infos, t_object *obj,
								double check_angle, int *orientation);

void		actualize_doors(t_infos *infos, t_door *door, double elapsed_time);
void		add_door(t_infos *infos, t_file *file, t_list *node);
t_door		*get_door(t_infos *infos);
int			is_on_door(t_infos *infos, int is_horizontal);

void		initialize_threads(t_thread *thread, t_infos *infos, int *t_x);
void		draw_threads(t_infos *infos);
void		*predraw(void *thread);
void		draw(t_infos *infos, int x);
void		draw_column(t_infos *infos, int screen_x, double angle,
							int floor_start);
void		draw_floor_sky(t_infos *infos, int screen_x,
						double angle, int floor_start);
int			get_color(int original_color, double color_r);
int			get_texture_x(t_infos *infos, t_texture *text);

void		draw_sky_color(t_infos *infos, int screen_x, int sky_end);
void		draw_sky_texture(t_infos *infos, int screen_x, int sky_end);
int			get_floor_color(int original_color, int dist);
void		draw_floor_color(t_infos *infos, int screen_x, int y);
void		draw_floor_texture(t_infos *infos, int x, double angle, int y);

int			hp_color(double hp);
void		draw_hb_int(t_infos *infos);
void		draw_hb_ext(t_infos *infos, t_coord *hp_start, t_ratio *r);

void		draw_inventory(t_infos *infos, t_hud *inv);
void		draw_hud(t_infos *infos);
void		draw_weapon(t_infos *infos, t_hud *weapon);

void		ft_warning(char *msg, ...);
void		ft_error(t_infos *infos, char *msg, ...);
void		ft_map_error(t_infos *infos, t_list *head, char *msg, ...);

void		set_own_hud_texture(t_infos *infos, char *filename, t_hud *hud);
void		set_own_texture(t_infos *infos, char *filename, t_texture *texture);
void		initialize_keys(t_infos *infos);
void		initialize_textures2(t_infos *infos);
void		initialize_textures(t_infos *infos);

int			tick_event(t_infos *infos);
int			key_press(int keycode, t_infos *infos);
void		key_press2(int keycode, t_infos *infos);
int			key_release(int keycode, t_infos *infos);
void		key_release2(int keycode, t_infos *infos);

void		next_level(t_infos *infos);
int			ennemies_alive(t_sprite *sprite);
void		sprite_dies(t_infos *infos);
void		game_over(t_infos *infos);
void		kill_them_all(t_infos *infos);

void		move_up(t_infos *infos, t_object *obj);
void		move_down(t_infos *infos, t_object *obj);
void		move_left(t_infos *infos, t_object *obj);
void		move_right(t_infos *infos, t_object *obj);
void		move(t_infos *infos);

double		raycast(t_infos *infos, t_object *source, double angle);
double		raycast_e(t_infos *infos, t_object *source, double angle);
double		raycast_n(t_infos *infos, t_object *source, double angle);
double		raycast_w(t_infos *infos, t_object *source, double angle);
double		raycast_s(t_infos *infos, t_object *source, double angle);

void		init_raycast_e(t_infos *infos, t_object *source,
						double angle, t_ray_infos *ray);
void		init_raycast_n(t_infos *infos, t_object *source,
						double angle, t_ray_infos *ray);
void		init_raycast_w(t_infos *infos, t_object *source,
						double angle, t_ray_infos *ray);
void		init_raycast_s(t_infos *infos, t_object *source,
						double angle, t_ray_infos *ray);
void		set_wall_orientation(t_infos *infos, int is_horizontal,
								int dir, int raycast_o);

void		set_hud_limits(t_hud *hud);
void		set_hud_start_x(t_hud *hud);
void		set_hud_end_x(t_hud *hud);

int			can_slide(t_infos *infos, int o, double angle);
void		slide(t_infos *infos, int o, double angle);

long		timediff(t_timespec old, t_timespec new);
void		free_lists(t_infos *infos);
void		free_all(t_infos *infos);
double		true_angle(double nb);
int			ft_exit(t_infos *infos);

void		get_sprite_angles(t_sprite *sprite, t_object *player,
								t_texture *texture);
void		calculate_sprite_infos(t_infos *infos);

void		set_sprite_ratio(t_sprite *sprite, t_texture *sprite_frame,
							double angle);
void		set_sprite_x_startend(t_sprite *sprite, int x);
int			is_in_sprite(t_sprite *sprite, double angle);
void		draw_sprites(t_infos *infos, double angle, double wall_dist, int x);
void		draw_sprite(t_infos *infos, t_sprite *sprite, int screen_x,
							int limit);

void		set_ratio_xy(t_hud *hud, t_sprite *sprite, double *rx, double *ry);
void		draw_sprites_life(t_infos *infos, t_sprite *sprite);
void		draw_sprite_hb_int(t_infos *infos, t_sprite *sprite);
void		draw_sprite_hb_ext(t_infos *infos, t_sprite *sprite,
							t_coord *hp_start, t_ratio *r);

int			ft_abs(int x);
double		inverse_move(double move);
double		path(t_infos *infos, t_sprite *sprite, double first, double second);
int			pathfinding(t_infos *infos, t_sprite *sprite);

int			sprite_lst_size(t_sprite *list);
void		sort_array(t_sprite **array, int size);
void		sort_sprites(t_sprite **list, int size);

void		set_sprite_move_frame(t_timespec *move_time, int *sprite_frame);
void		damage_player(t_infos *infos, double damage);
void		attack_player(t_infos *infos, t_sprite *sprite);
void		activate_sprites(t_infos *infos);
void		sprite_move_to_player(t_infos *infos, t_sprite *sprite);

double		get_size_mult(int type);
void		initialize_sprite(t_sprite *sprite);
void		add_sprite(t_infos *infos, int type, t_file *file, t_list *node);

void		check_line(t_list *node, t_infos *infos, t_file *file);
int			check_border(t_infos *infos, t_list *node, t_file *file);
int			check_middle(t_list *node, t_file *file, t_infos *infos);
void		check_character(char c, t_infos *infos, t_file *file, t_list *node);
double		get_angle(char c);

void		init_option(t_option *option, char *id, t_fct fct);
void		init_options(t_option *options);

void		lst_purge(t_list *head);
void		lst_add_back(t_infos *infos, t_list **head, void *content);
int			lst_size(t_list *list);

void		parse_map(t_file *file, t_infos *infos, char *buffer);
void		fill_map(t_list *node, t_infos *infos, t_file *file);
void		format_line(char *dest, char *src);

void		parser(t_infos *infos, char *path);
void		init_infos(t_infos *infos);
void		parse_options(t_file *file, t_infos *infos, t_option *options,
						char **buffer_start);
void		set_option(t_option *options, t_file *file, t_infos *infos);
void		check_options(t_infos *infos);

int			calculate_color(t_infos *infos, t_file *file, char *id);
void		set_color(t_file *file, t_infos *infos, char *id);
void		switch_color_texture(t_file *file, t_infos *infos, char *id);

void		set_resolution(t_file *file, __attribute__((unused))
						t_infos *infos, __attribute__((unused)) char *id);
void		set_resolution_width(t_infos *infos, t_file *file);
void		set_resolution_height(t_infos *infos, t_file *file);

void		set_texture(t_file *file, t_infos *infos, char *id);
int			get_texture_id(char *id);
void		set_texture_ratios(t_texture *texture);

void		skip_spaces(t_infos *infos, t_file *file, int is_required);
void		endofline(t_infos *infos, t_file *file);
void		skip_map_spaces(char *line, int *i);
void		remove_end_spaces(char *line);

int			path_is_valid(char *path, char *extension);
int			get_number(t_file *file);
int			idcmp(t_file *file, char *id);

#endif
