INCLUDE_BASE		= base/base.h
SRCS_BASE			= $(addprefix base/, ft_strlen.c ft_isdigit.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c \
					ft_atoi.c ft_calloc.c ft_strdup.c square.c ft_strcmp.c)
OBJS_BASE			= ${SRCS_BASE:.c=.o}

INCLUDE_GNL			= gnl/get_next_line.h
SRCS_GNL			= $(addprefix gnl/, get_next_line.c get_next_line_utils.c)
OBJS_GNL			= ${SRCS_GNL:.c=.o}

INCLUDE_PRINTF		= ft_printf/ft_printf.h
SRCS_PRINTF			= $(addprefix ft_printf/, ft_printf.c convertarg.c dict.c get_basics.c \
					get_numbers.c list.c utils.c utils_numbers.c \
					utils_str.c fill_buffer.c \
					get_bonus.c utils_bonus.c set_bonus.c unicode.c \
					unicode2.c fill_buffer_bonus.c getarg.c selfbonus.c macro.c)
SRCS_PRINTF			+= base/ft_isdigit.c
OBJS_PRINTF			= ${SRCS_PRINTF:.c=.o}

INCLUDE_DPRINTF		= ft_dprintf/ft_dprintf.h
SRCS_DPRINTF		= $(addprefix ft_printf/, convertarg.c dict.c get_basics.c \
					get_numbers.c list.c utils.c utils_numbers.c \
					utils_str.c fill_buffer.c \
					get_bonus.c utils_bonus.c set_bonus.c unicode.c \
					unicode2.c fill_buffer_bonus.c getarg.c selfbonus.c macro.c) \
					$(addprefix ft_dprintf/, ft_dprintf.c)
SRCS_DPRINTF		+= base/ft_isdigit.c
OBJS_DPRINTF		= ${SRCS_DPRINTF:.c=.o} 

all:				libbase.a libgnl.a libprintf.a libdprintf.a

$(OBJS_BASE):		${INCLUDE_BASE}
$(OBJS_GNL):		${INCLUDE_GNL}
$(OBJS_PRINTF):		${INCLUDE_PRINTF}
$(OBJS_DPRINTF):	${INCLUDE_DPRINTF}

libbase.a:			${OBJS_BASE}
					ar -rcs libbase.a ${OBJS_BASE}
libgnl.a:			${OBJS_GNL}
					ar -rcs libgnl.a ${OBJS_GNL}
libprintf.a:		${OBJS_PRINTF}
					ar -rcs libprintf.a ${OBJS_PRINTF}
libdprintf.a:		${OBJS_DPRINTF}
					ar -rcs libdprintf.a ${OBJS_DPRINTF}

.c.o:
					gcc ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
					rm -rf ${OBJS_BASE} ${OBJS_GNL} ${OBJS_PRINTF} ${OBJS_DPRINTF}

fclean:				clean
					rm -rf libbase.a libgnl.a libprintf.a libdprintf.a

re:					fclean all

.PHONY:				all clean fclean re
