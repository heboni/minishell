/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:15:23 by heboni            #+#    #+#             */
/*   Updated: 2022/10/14 17:12:34 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin_print(t_env *envs)
{
	while (envs)
	{
		if (envs->var_value)
			printf("%s=%s\n", envs->var_name, envs->var_value);
		envs = envs->next;
	}
}

// env with no options or arguments
int	env_builtin(t_msh *msh_ctx)
{
	char	**argv;

	if (!msh_ctx->env_lst || !msh_ctx->node->argv)
		return (-1);
	argv = msh_ctx->node->argv + 1;
	if (*argv)
	{
		printf("bash: env: can't be executed with arguments\n");
		return (1);
	}
	else
		env_builtin_print(msh_ctx->env_lst);
	return (0);
}
