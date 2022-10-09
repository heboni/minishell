/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:21:59 by heboni            #+#    #+#             */
/*   Updated: 2022/10/10 09:45:36 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# include <signal.h>

int	exit_builtin(t_msh *msh_ctx) //exit #include <stdlib.h> //завершает текущий процесс, переходит к родительскому
{
	int	code;
	int	is_num;
	
	is_num = 1;
	if (msh_ctx->node->argv[2] != NULL)
	{
		printf("bash: exit: too many arguments\n");
	}
	if (msh_ctx->node->argv[1] != NULL)
	{
		(void)msh_ctx; //?
		printf("exit: Всем пока!!\n");
		code = ft_atoi(msh_ctx->node->argv[1], &is_num);
		if (is_num == 0)
			printf("bash: exit: numeric argument required\n");
		msh_ctx->status = code; //мб излишне, тк waitpid поймает код завершения
		exit(msh_ctx->node->argv[1]);
	}
	else
	{
		(void)msh_ctx; //?
		printf("exit: Всем пока!!\n");
		exit(msh_ctx->status);
	}
}

// int	main(void)
// {
// 	pid_t ppid = getppid();
// 	exit_builtin(ppid);
// 	return (0);
// }