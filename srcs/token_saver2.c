/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_saver2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:19:29 by heboni            #+#    #+#             */
/*   Updated: 2022/10/14 10:20:59 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	regular_char_token_part(char **tokens, int t_n, int i, t_msh *msh_ctx)
{
	if ((msh_ctx->line)[i] == '\'')
	{
		single_quote_token_saver(tokens, t_n, i, msh_ctx);
		return (1);
	}
	if ((msh_ctx->line)[i] == '\"')
	{
		double_quotes_token_saver(tokens, t_n, i, msh_ctx);
		return (1);
	}
	return (0);
}

int	regular_char_token_part2(char **tokens, int t_n, int *i, t_msh *msh_ctx)
{
	if ((msh_ctx->line)[*i] == '$' && (msh_ctx->line)[*i + 1] != ' ' && \
			(msh_ctx->line)[*i + 1] != '\0' && (msh_ctx->line)[*i + 1] != '?')
	{
		*i = get_env_var_value_to_saver(tokens, t_n, *i + 1, msh_ctx) + 1;
		return (1);
	}
	if ((msh_ctx->line)[*i] == '$' && (msh_ctx->line)[*i + 1] == '?')
	{
		*i = handle_status_from_saver(tokens, t_n, *i + 1, msh_ctx) + 1;
		return (1);
	}
	return (0);
}

int	special_here(t_msh *msh_ctx, int i)
{
	if ((msh_ctx->line)[i] == '|' || (msh_ctx->line)[i + 1] == '|' || \
		(msh_ctx->line)[i] == '>' || (msh_ctx->line)[i + 1] == '>' || \
		(msh_ctx->line)[i] == '<' || (msh_ctx->line)[i + 1] == '<')
		return (1);
	return (0);
}

void	regular_char_token_saver(char **tokens, int t_n, int i, t_msh *msh_ctx)
{
	int	k;

	while (1)
	{
		k = ft_strlen(tokens[t_n]) - 1;
		if (regular_char_token_part(tokens, t_n, i, msh_ctx))
			return ;
		if (regular_char_token_part2(tokens, t_n, &i, msh_ctx))
			continue ;
		if ((msh_ctx->line)[i] == ' ' || (msh_ctx->line)[i] == '\0')
			break ;
		tokens[t_n][++k] = (msh_ctx->line)[i];
		if (special_here(msh_ctx, i))
			break ;
		i++;
	}
	tokens[t_n][++k] = '\0';
}
