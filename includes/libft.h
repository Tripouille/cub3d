/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 11:09:44 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/16 11:09:44 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>

size_t				ft_strlen(const char *s);
int					ft_isdigit(int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strlcpy(char *dst, const char *rsc, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
double				square(double x);

int					get_next_line(int fd, char **line);

int					ft_printf(const char *s, ...);

int					ft_dprintf(int fd, const char *s, ...);

#endif
