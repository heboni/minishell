/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 18:46:23 by heboni            #+#    #+#             */
/*   Updated: 2022/10/09 16:05:37 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*s_buf;
	char	cc;

	cc = c;
	s_buf = (char *)s;
	while (*s_buf)
	{
		if (*s_buf == cc)
			return (s_buf);
		s_buf++;
	}
	if (c == '\0')
		return (s_buf);
	return (((void *)0));
}
