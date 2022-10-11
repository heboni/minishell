/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 18:51:56 by heboni            #+#    #+#             */
/*   Updated: 2022/10/12 00:00:39 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = -1;
	while (src[++i] != '\0')
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

char	*ft_strcpy_end(char *dst, const char *src)
{
	int	i;
	int	l;

	i = -1;
	l = ft_strlen(dst) - 1;
	while (src[++i] != '\0')
		dst[++l] = src[i];
	dst[++l] = '\0';
	return (dst);
}
