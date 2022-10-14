/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:20:05 by heboni            #+#    #+#             */
/*   Updated: 2022/10/14 13:42:08 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_chdir(t_msh *msh_ctx, char	*dir_to, char *old_dir, char *new_dir)
{
	if (chdir(dir_to) != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", dir_to);
		free(old_dir);
		return (1);
	}
	else
	{
		new_dir = getcwd(NULL, 0);
		if (!env_lst_update_node(msh_ctx->env_lst, "PWD", new_dir))
			env_lst_push_bottom(&(msh_ctx->env_lst), "PWD", new_dir);
		if (!env_lst_update_node(msh_ctx->env_lst, "OLDPWD", old_dir))
			env_lst_push_bottom(&(msh_ctx->env_lst), "OLDPWD", old_dir);
		free(old_dir);
		free(new_dir);
	}
	return (0);
}

int	cd_builtin(t_msh *msh_ctx)
{
	char	**argv;
	char	*new_dir;
	char	*old_dir;
	char	*dir_to;

	argv = msh_ctx->node->argv + 1;
	old_dir = getcwd(NULL, 0);
	new_dir = NULL;
	if (*argv == NULL)
		dir_to = getenv("HOME");
	else
		dir_to = *argv;
	return (exec_chdir(msh_ctx, dir_to, old_dir, new_dir));
}
