/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:21:59 by heboni            #+#    #+#             */
/*   Updated: 2022/10/10 20:28:55 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_builtin(t_msh *msh_ctx) //exit #include <stdlib.h> //завершает текущий процесс, переходит к родительскому
{
	int	code;
	int	is_num;
	int argv_count;
	
	is_num = 1;
	argv_count = len_2d_array(msh_ctx->node->argv); printf("%d\n", argv_count);
	if (argv_count > 2)
	{
		printf("bash: exit: too many arguments\n");
		return (1);
	}
	(void)msh_ctx; //?
	printf("exit: Всем пока!!\n");
	if (argv_count == 2)
	{
		code = ft_atoi(msh_ctx->node->argv[1], &is_num);
		if (is_num == 0)
			printf("bash: exit: numeric argument required\n");
		msh_ctx->status = code; //мб излишне, тк waitpid поймает код завершения
		exit(code);
	}
	else
		exit(msh_ctx->status);
}

// int	main(void)
// {
// 	pid_t ppid = getppid();
// 	exit_builtin(ppid);
// 	return (0);
// }