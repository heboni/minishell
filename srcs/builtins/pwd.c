/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:58:04 by heboni            #+#    #+#             */
/*   Updated: 2022/10/09 16:43:16 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(int fd)
{
	char	*dir;

	dir = getcwd(NULL, 0); //dir и buf указывают на один и тот же кусок памяти
	if (dir == NULL)
		return (1);
	ft_putstr_fd(dir, fd);
	write(fd, "\n", 1);
	free(dir);
	return (0);
}

// int	main(void)
// {
// 	pwd(1);
// 	return (0);
// }