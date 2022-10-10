/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:58:04 by heboni            #+#    #+#             */
/*   Updated: 2022/10/10 18:51:17 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(t_msh *msh_ctx)
{
	char	*dir;

	(void)msh_ctx;
	dir = getcwd(NULL, 0); //dir и buf указывают на один и тот же кусок памяти
	if (dir == NULL)
	{
		ft_putstr_fd("bash : getcwd error\n", 1);
		return (1);
	}
	printf("%s\n", dir);
	// ft_putstr_fd(dir, 1);
	// write(1, "\n", 1);
	free(dir);
	return (0);
}

// int	main(void)
// {
// 	pwd_builtin(1);
// 	return (0);
// }