/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_lst_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:26:25 by heboni            #+#    #+#             */
/*   Updated: 2022/10/12 09:37:02 by heboni           ###   ########.fr       */
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
	printf("[env_lst_remove_node] n_node %s, %s\n", \
		n_node->var_name, n_node->var_value);
	if (n == 1)
		*envs = n_node->next;
	else
	{
		prev = get_n_env_node(*envs, n - 1);
		prev->next = n_node->next;
	}
	free(n_node->var_name);
	free(n_node->var_value);
	free(n_node);
	print_env_list(*envs);
}

void	print_env_list(t_env *envs)
{
	printf("\n---------------print_envs--------------\n");
	if (!envs)
		return ;
	while (envs)
	{
		printf("%s, ", (char *)envs->var_name);
		printf("%s \n", (char *)envs->var_value);
		envs = envs->next;
	}
	printf("\n");
}
