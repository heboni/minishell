/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 01:24:27 by heboni            #+#    #+#             */
/*   Updated: 2022/10/14 01:25:39 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pass_env_var_value_from_lexer(char *line, int i, t_msh *msh_ctx)
{
	char	*var_name;
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
	var_name = get_env_name_from_line(line, tmp_i, var_len);
	env_val_len_by_name_from_lst(var_name, msh_ctx);
	free(var_name);
	return (i - 1);
}

void	env_val_len_by_name_from_lst(char *name, t_msh *msh_ctx)
{
	t_env	*tmp;

	if (!msh_ctx->env_lst)
		return ;
	tmp = msh_ctx->env_lst;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->var_name) == 0)
			msh_ctx->cur_env_vars_len += ft_strlen(tmp->var_value);
		tmp = tmp->next;
	}
	msh_ctx->cur_env_vars_len -= ft_strlen(name);
	msh_ctx->cur_env_vars_len--;
}
