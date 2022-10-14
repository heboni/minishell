/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_lst_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:26:25 by heboni            #+#    #+#             */
/*   Updated: 2022/10/14 20:18:32 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_n_env_node(t_env *envs, int n)
{
	int		i;
	t_env	*n_node;

	i = 0;
	while (++i < n)
		envs = envs->next;
	n_node = envs;
	return (n_node);
}

void	env_lst_remove_n_node(t_env **envs, int n)
{
	t_env	*prev;
	t_env	*n_node;

	if (!envs)
		return ;
	n_node = get_n_env_node(*envs, n);
	if (n == 1)
		*envs = n_node->next;
	else
	{
		prev = get_n_env_node(*envs, n - 1);
		prev->next = n_node->next;
	}
	free(n_node->var_name);
	n_node->var_name = NULL;
	free(n_node->var_value);
	n_node->var_value = NULL;
	free(n_node);
	n_node = NULL;
}

int	get_envs_count(t_env *envs)
{
	int	envs_count;

	envs_count = 0;
	while (envs)
	{
		envs_count++;
		envs = envs->next;
	}
	return (envs_count);
}

void	export_print_env_list(t_env *envs)
{
	if (!envs)
		return ;
	while (envs)
	{
		printf("declare -x %s", envs->var_name);
		if (envs->var_value)
			printf("=\"%s\"", envs->var_value);
		printf("\n");
		envs = envs->next;
	}
}

char	*get_env_name_to_buildin(char *argv, int *k)
{
	char	*name;
	int		i;

	i = -1;
	while (argv[++i] != '=' && argv[i] != '\0' && \
			!(argv[i] == '\"' && argv[i + 1] == '=') \
			&& !(argv[i] == '\'' && argv[i + 1] == '='))
	{
	}
	name = NULL;
	name = (char *)malloc(sizeof(char) * i + 1);
	if (name == NULL)
		exit(STACK_OVERFLOW);
	*k = -1;
	while (++(*k) < i)
		name[*k] = argv[*k];
	name[*k] = '\0';
	return (name);
}
