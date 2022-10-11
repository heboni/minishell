/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:16:57 by heboni            #+#    #+#             */
/*   Updated: 2022/10/12 00:21:17 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strcpy_end(char *dst, const char *src); //?
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_3(char const *s1, char const *s2, char const *s3);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr_fd_nl(char *optional, char *s, int fd, int nl);
int		ft_atoi(const char *str, int *is_num);
char	*ft_itoa(int n);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		is_space(char c);

#endif