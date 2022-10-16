/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:21:59 by heboni            #+#    #+#             */
/*   Updated: 2022/10/16 19:07:35 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//exit #include <stdlib.h> 
//завершает текущий процесс, переходит к родительскому
int	exit_builtin(t_msh *msh_ctx)
{
	int	code;
	int	is_num;
	int	argv_count;

	is_num = 1;
	argv_count = len_2d_array(msh_ctx->node->argv);
	if (argv_count > 2)
	{
		printf("bash: exit: too many arguments\n");
		return (1);
	}
	printf("exit: Всем пока!!\n");
	if (argv_count == 2)
	{
		code = ft_atoi(msh_ctx->node->argv[1], &is_num);
		if (is_num == 0)
		{
			printf("bash: exit: numeric argument required\n");
			exit(255);
		}
		exit(code);
	}
	else
		exit(g_lobal_status);
}
