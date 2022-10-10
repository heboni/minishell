/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 17:57:12 by heboni            #+#    #+#             */
/*   Updated: 2021/10/24 17:57:15 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	a_power_m(int a, int m)
{
	int	res;
	int	i;

	i = -1;
	res = 1;
	while (++i < m)
		res = res * a;
	return (res);
}

static int	ft_digits_counter(int n)
{
	int	len;
	int	nbr;

	len = 1;
	if (n < 0)
	{
		len++;
		nbr = n * (-1);
	}
	else
		nbr = n;
	nbr = nbr / 10;
	while (nbr > 0)
	{
		len++;
		nbr = nbr / 10;
	}
	return (len);
}

static char	*ft_itoa_solver(int n, int len)
{
	char	*res;
	int		i;
	int		j;

	res = (char *)malloc(sizeof(char) * len + 1);
	if (res == ((void *)0))
		return (((void *)0));
	i = -1;
	j = len;
	if (n < 0)
	{
		j = len - 1;
		n = n * (-1);
		res[++i] = '-';
	}
	while (++i < len)
	{
		res[i] = (n / (a_power_m(10, j - 1))) + '0';
		n = n % a_power_m(10, j-- - 1);
	}
	res[len] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*res;

	if (n == -2147483648)
		return (ft_strjoin("-2147483648", "\0"));
	len = ft_digits_counter(n);
	res = ft_itoa_solver(n, len);
	return (res);
}
