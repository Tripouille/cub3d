NAME				= cub3D

INCLUDES			= $(addprefix includes/, cub3d.h libft.h mlx.h define.h struct.h)
SRCS				= $(addprefix srcs/, cub3d.c raycast_utils.c raycast.c move.c slide.c draw.c key.c \
						error.c utils.c draw_hud.c draw_floor_sky.c attack.c set_hud_limits.c animation.c \
						level_end.c initializer_utils.c crosshair.c draw_hb.c actualize.c distance.c \
						bmp.c door.c draw_column.c)
SRCS				+= $(addprefix srcs/parser/, parser.c init_options.c set_resolution.c set_color.c \
						set_texture.c skip.c map.c lst.c check_line.c utils_parser.c)
SRCS				+= $(addprefix srcs/sprite/, calculate_sprite_infos.c stock_sprite.c draw_sprite.c \
						sort_sprites.c sprite_action.c draw_sprite_life.c pathfinding.c)

OBJS				= ${SRCS:.c=.o}

CFLAGS				= -g3 -Wall -Wextra -Werror -I includes

all:				${NAME}

.c.o:
					gcc ${CFLAGS} -c $< -o ${<:.c=.o}

$(OBJS):			${INCLUDES}

lib:
					make -C srcs_lib/
					make -C mlx/

$(NAME):			lib ${INCLUDES} ${OBJS}
					gcc ${CFLAGS} -lmlx -Lmlx -lbase -lgnl -ldprintf -lprintf \
					-Lsrcs_lib -framework OpenGl -framework AppKit ${OBJS} -o ${NAME}

bonus:				all

clean:
					make fclean -C srcs_lib/
					make clean -C mlx/
					rm -rf ${OBJS}

fclean:				clean
					rm -rf ${NAME}

re:					fclean all

.PHONY:				all lib bonus clean fclean re
