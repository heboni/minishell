/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 09:23:29 by heboni            #+#    #+#             */
/*   Updated: 2022/10/12 11:10:16 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_var_value_to_saver(char **tokens, int t_n, int i, t_msh *msh_ctx)
{
	char	*var_name;
	char	*var_value;
	int		var_len;
	int		tmp_i;

	var_len = 0;
	tmp_i = i;
	while (!is_space((msh_ctx->line)[i]))
	{
		if ((msh_ctx->line)[i] == '\0' || (msh_ctx->line)[i] == '$' \
		|| (msh_ctx->line)[i] == '\"' || (msh_ctx->line)[i] == '\'')
			break ;
		var_len++;
		i++;
	}
	var_name = (char *)malloc(sizeof(char) * var_len + 1);
	if (var_name == NULL)
		exit(STACK_OVERFLOW);
	get_env_name_from_line(&var_name, msh_ctx->line, tmp_i);
	var_value = get_env_value_by_name_from_envs(var_name, msh_ctx);
	free(var_name);
	put_env_value_to_token(var_value, tokens, t_n);
	return (i - 1);
}

void	put_env_value_to_token(char *var_value, char **tokens, int token_n)
{
	int		k;

	k = ft_strlen(tokens[token_n]) - 1;
	if (var_value)
	{
		while (*var_value)
		{
			tokens[token_n][++k] = *var_value;
			var_value++;
		}
	}
	tokens[token_n][++k] = '\0';
}

int	get_env_var_value_to_lexer(char *line, int i, t_msh *msh_ctx)
{
	char	*var_name;
	char	*var_value;
	int		var_len;
	int		tmp_i;

	var_len = 0;
	tmp_i = i;
	while (!is_space(line[i]))
	{
		if (line[i] == '\0' || line[i] == '$' \
			|| line[i] == '\"' || line[i] == '\'')
			break ;
		var_len++;
		i++;
	}
	var_name = (char *)malloc(sizeof(char) * var_len + 1);
	if (var_name == NULL)
		exit(STACK_OVERFLOW);
	get_env_name_from_line(&var_name, line, tmp_i);
	var_value = NULL;
	var_value = get_env_value_by_name_from_envs(var_name, msh_ctx);
	free(var_name);
	return (i - 1);
}

void	get_env_name_from_line(char **var_name, char *line, int tmp_i)
{
	int	j;

	j = 0;
	while (!is_space(line[tmp_i]))
	{
		if (line[tmp_i] == '\0' || line[tmp_i] == '$' \
			|| line[tmp_i] == '\'' || line[tmp_i] == '\"')
			break ;
		(*var_name)[j] = line[tmp_i];
		tmp_i++;
		j++;
	}
	(*var_name)[j] = '\0';
}

char	*get_env_value_by_name_from_envs(void *name, t_msh *msh_ctx)
{
	t_env	*tmp;

	if (!msh_ctx->env_lst)
		return (NULL);
	tmp = msh_ctx->env_lst;
	while (tmp)
	{
		if (ft_strcmp((char *)name, (char *)tmp->var_name) == 0)
		{
			msh_ctx->cur_env_vars_len += ft_strlen((char *)tmp->var_value);
			return ((char *)tmp->var_value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
