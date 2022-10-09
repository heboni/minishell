/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 09:49:28 by heboni            #+#    #+#             */
/*   Updated: 2022/10/09 16:42:06 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_echo_delimiter(char **argv, int n_flag)
{
	char	*c;

	if (*argv != NULL)
		c = " ";
	else
	{
		c = "\n";
		if (n_flag)
			c = "\0";
	}
	return (c);
}

int	echo(char **argv, int fd)
{
	int		len;
	int		returned_v;
	int		n_flag;
	char	*c;

	n_flag = 0;
	if (ft_strcmp("-n", *argv) == 0)
	{
		n_flag = 1;
		argv++;
	}
	while (*argv)
	{
		len = ft_strlen(*argv);
		returned_v = write(fd, *argv, len);
		if (returned_v == -1)
			return (1);
		argv++;
		c = get_echo_delimiter(argv, n_flag);
		returned_v = write(fd, c, 1);
		if (returned_v == -1)
			return (1);
	}
	return (0);
}

// int	main(void)
// {
// 	char	*argv[4] = {"-", "ab", NULL, NULL};

// 	echo(argv, 1);
// 	return (0);
// }
