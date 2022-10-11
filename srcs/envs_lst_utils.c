/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_lst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 08:58:55 by heboni            #+#    #+#             */
/*   Updated: 2022/10/12 09:27:49 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_lst_push_bottom(t_env **head, char *name, char *value)
{
	t_env	*new;
	t_env	*last_node;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		exit(STACK_OVERFLOW);
	new->var_name = ft_strdup(name);
	if (value)
		new->var_value = ft_strdup(value);
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return ;
	}
	last_node = get_last_node(*head);
	last_node->next = new;
}

t_env	*get_last_node(t_env *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	free_env_lst(t_env **lst)
{
	t_env	*next;

	if (!lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->var_name);
		free((*lst)->var_value);
		free(((*lst)));
		*lst = next;
	}
}

int	get_env_n_if_exists(t_env *envs, char *name)
{
	int	n;

	n = 1;
	while (envs)
	{
		if (ft_strcmp(envs->var_name, name) == 0)
			return (n);
		n++;
		envs = envs->next;
	}
	return (0);
}

int	env_lst_update_node(t_env *envs, char *name, char *value)
{
	while (envs)
	{
		if (ft_strcmp(envs->var_name, name) == 0)
		{
			free(envs->var_value);
			envs->var_value = ft_strdup(value);
			return (1);
		}
		envs = envs->next;
	}
	return (0);
}
