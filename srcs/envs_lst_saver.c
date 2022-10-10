/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_lst_saver.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:28:42 by heboni            #+#    #+#             */
/*   Updated: 2022/09/18 22:58:33 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envs_saver(char **env, t_env **envs_lst)
{
	char 	*name;
	char	*value;
	int		i;
	int 	k;
	
	while (*env)
	{
		i = -1;
		while ((*env)[++i] != '=') {}
		name = (char *)malloc(sizeof(char) * i + 1); 
		if (name == NULL)
			exit(STACK_OVERFLOW);
		k = -1;
		while (++k < i)
			name[k] = (*env)[k];
		name[k] = '\0';
		k++; //после '='
		i++; //после '='
		while ((*env)[i++] != '\0') {}
		value = get_env_value_to_save(*env, i, k);
		env_lst_push_bottom(envs_lst, name, value);
		free(name);
		free(value);
		env++;
	}
}

char	*get_env_value_to_save(char *env, int i, int k)
{
	char	*value;
	int		l;

	l = 0;
	value = (char *)malloc(sizeof(char) * (i - k) + 1);
	if (value == NULL)
		exit(STACK_OVERFLOW);
	while (l < (i - k))
	{
		value[l] = env[k + l];
		l++;
	}
	value[l] = '\0';
	return (value);
}

char	**envs_lst_to_char_array(t_env *env_lst)
{
	char	**envs;
	t_env	*tmp_lst;
	int		envs_count;
	int		i;

	envs = NULL;
	tmp_lst = env_lst;
	envs_count = 0;
	i = -1;
	while (tmp_lst)
	{
		envs_count++;
		tmp_lst = tmp_lst->next;
	}
	envs = (char **)malloc(sizeof(char *) * (envs_count + 1));
	if (envs == NULL)
		exit(STACK_OVERFLOW);
	while (env_lst)
	{
		envs[++i] = ft_strjoin_3(env_lst->var_name, "=\0", env_lst->var_value);
		env_lst = env_lst->next;
	}
	envs[envs_count] = NULL;
	return (envs);
}
