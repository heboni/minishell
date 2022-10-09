/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 14:53:11 by heboni            #+#    #+#             */
/*   Updated: 2022/10/09 16:05:55 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] == s2[i])
	{
		if (s1[i] == '\0' || i == n - 1)
			return (0);
		i++;
	}
	if (s1[i] == '\200' && s2[i] == '\0')
		return (1);
	if (s1[i] == '\0' && s2[i] == '\200')
		return (1);
	c1 = s1[i];
	c2 = s2[i];
	return (c1 - c2);
}
