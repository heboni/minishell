/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 18:50:43 by heboni            #+#    #+#             */
/*   Updated: 2021/10/24 18:50:46 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		len1;
	int		len2;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s = (char *)malloc(sizeof(char) * (len1 + len2) + 1);
	if (s == ((void *)0))
		return (((void *)0));
	i = -1;
	while (++i < len1)
		s[i] = s1[i];
	j = -1;
	while (++j < len2)
		s[i + j] = s2[j];
	s[i + j] = '\0';
	return (s);
}
