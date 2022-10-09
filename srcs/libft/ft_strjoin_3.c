/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 18:50:43 by heboni            #+#    #+#             */
/*   Updated: 2022/10/09 17:15:24 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*fill_s(int *lens, char const *s1, char const *s2, char const *s3)
{
	char	*s;
	int		i;
	int		j;
	int		k;

	s = (char *)malloc(sizeof(char) * (lens[0] + lens[1] + lens[2]) + 1);
	if (s == NULL)
		exit (-1);
	i = -1;
	while (++i < lens[0])
		s[i] = s1[i];
	j = -1;
	while (++j < lens[1])
		s[i + j] = s2[j];
	k = -1;
	while (++k < lens[2])
		s[i + j + k] = s3[k];
	s[i + j + k] = '\0';
	return (s);
}

char	*ft_strjoin_3(char const *s1, char const *s2, char const *s3)
{
	char	*s;
	int		*lens;
	int		len1;
	int		len2;
	int		len3;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	lens = (int *)malloc(sizeof(int) * 3);
	if (lens == NULL)
		exit (-1);
	lens[0] = len1;
	lens[1] = len2;
	lens[2] = len3;
	s = fill_s(lens, s1, s2, s3);
	free(lens);
	return (s);
}
