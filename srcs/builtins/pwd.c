/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:58:04 by heboni            #+#    #+#             */
/*   Updated: 2022/10/14 11:15:44 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(t_msh *msh_ctx)
{
	char	*dir;

	(void)msh_ctx;
	dir = getcwd(NULL, 0);
	if (dir == NULL)
	{
		ft_putstr_fd("bash : getcwd error\n", 1);
		return (1);
	}
	printf("%s\n", dir);
	free(dir);
	return (0);
}
