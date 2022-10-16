/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 23:17:49 by heboni            #+#    #+#             */
/*   Updated: 2022/10/16 19:06:58 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envs_swap(t_env *tmp_envs)
{
	char	*tmp_name;
	char	*tmp_value;

	tmp_name = tmp_envs->var_name;
	tmp_value = tmp_envs->var_value;
	tmp_envs->var_name = (tmp_envs->next)->var_name;
	tmp_envs->var_value = (tmp_envs->next)->var_value;
	(tmp_envs->next)->var_name = tmp_name;
	(tmp_envs->next)->var_value = tmp_value;
}

void	alphabetical_envs_print(t_env *envs)
{
	t_env	*tmp_envs;
	int		envs_count;
	int		i;

	i = -1;
	envs_count = get_envs_count(envs);
	while (++i < envs_count)
	{
		tmp_envs = envs;
		while (tmp_envs)
		{
			if (tmp_envs->next)
			{
				if (tmp_envs->var_name[0] > (tmp_envs->next)->var_name[0])
					envs_swap(tmp_envs);
			}
			tmp_envs = tmp_envs->next;
		}
	}
	export_print_env_list(envs);
}

void	export_core(t_env *envs, char *argv, char *name, int k)
{
	char	*value;
	int		i;

	if (argv[k] != '\0')
	{
		if (argv[k] == '\'' || argv[k] == '\"')
			k = k + 3;
		else
			k++;
		i = k;
		while (argv[i++] != '\0')
		{
		}
		value = get_env_value_to_save(argv, i, k);
		if (!env_lst_update_node(envs, name, value))
			env_lst_push_bottom(&envs, name, value);
		free(value);
	}
	else
		env_lst_push_bottom(&envs, name, NULL);
}

void	export_arg_handler(t_msh *msh_ctx, char *argv)
{
	char	*name;
	int		k;

	name = get_env_name_to_buildin(argv, &k);
	if (is_not_valid(name))
	{
		printf("bash: export: '%s': not a valid identifier\n", name);
		g_lobal_status = 1;
	}
	else
		export_core(msh_ctx->env_lst, argv, name, k);
	free(name);
}

int	export_builtin(t_msh *msh_ctx)
{
	char	**argv;

	if (!msh_ctx->env_lst || !msh_ctx->node->argv)
		return (-1);
	argv = msh_ctx->node->argv + 1;
	if (!*argv)
		alphabetical_envs_print(msh_ctx->env_lst);
	else
	{
		while (*argv != NULL)
		{
			export_arg_handler(msh_ctx, *argv);
			argv++;
		}
	}
	if (g_lobal_status == 1)
		return (1);
	return (0);
}
