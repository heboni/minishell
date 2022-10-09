/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 18:44:34 by heboni            #+#    #+#             */
/*   Updated: 2022/10/09 23:27:40 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	if (fd < 0 || !s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}

void	ft_putstr_fd_nl(char *optional, char *s, int fd, int nl)
{
	if (fd < 0 || !s)
		return ;
	if (optional)
		write(fd, optional, ft_strlen(optional));
	write(fd, s, ft_strlen(s));
	if (nl)
		write(fd, "\n", 1);
}
