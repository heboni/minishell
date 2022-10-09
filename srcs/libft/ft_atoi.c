/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 21:44:20 by heboni            #+#    #+#             */
/*   Updated: 2022/10/10 09:43:42 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
# include <stdio.h>

int	has_letter(const char *s)
{
	int has_letter;

	has_letter = 0;
	while (*s)
	{
		if (!ft_isdigit(*s))
			has_letter = 1;
		s++;
	}
	return (has_letter);
}

int	ft_atoi(const char *str, int *is_num)
{
	int	n;
	int	neg;
	int	i;

	n = 0;
	i = 0;
	neg = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' \
			|| *str == '\v' || *str == '\r' || *str == '\f')
		str++;
	if (*str == '-')
		neg = -1;
	if (*str == '+' || *str == '-')
		str++;
	if (has_letter(str) || ft_strlen(str) > 9)
		*is_num = 0;
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

// int	main(void)
// {
// 	int	is_num;
	
// 	is_num = 1;
// 	char *a = "56783+";
// 	printf("%d\n", ft_atoi(a, &is_num));
// 	printf("is_num: %d\n", is_num);
// }
