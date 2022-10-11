/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 21:44:20 by heboni            #+#    #+#             */
/*   Updated: 2022/10/12 00:20:48 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	has_letter(const char *s)
{
	int	has_letter;

	has_letter = 0;
	while (*s)
	{
		if (!ft_isdigit(*s))
			has_letter = 1;
		s++;
	}
	return (has_letter);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' \
		|| c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

int	ft_atoi_inner(const char *str, int neg)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (++i > 18)
		{
			if (neg == 1)
				return (-1);
			return (0);
		}
		n = n * 10 + (*str++ - '0');
	}
	return (n * neg);
}

int	ft_atoi(const char *str, int *is_num)
{
	int	n;
	int	neg;

	neg = 1;
	while (is_space(*str))
		str++;
	if (*str == '-')
		neg = -1;
	if (*str == '+' || *str == '-')
		str++;
	if (has_letter(str) || ft_strlen(str) > 9)
		*is_num = 0;
	n = ft_atoi_inner(str, neg);
	return (n);
}
