/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:26:06 by heboni            #+#    #+#             */
/*   Updated: 2022/10/16 19:09:07 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_chars_lexer(char *line, int i)
{
	i++;
	if ((line[i - 1] == '>' && line[i] == '>') || \
				(line[i - 1] == '<' && line[i] == '<'))
		i++;
	return (i);
}

int	handle_status_from_lexer(int i, t_msh *msh_ctx)
{
	if (msh_ctx->s_status)
		free(msh_ctx->s_status);
	msh_ctx->s_status = ft_itoa(g_lobal_status);
	msh_ctx->cur_env_vars_len += ft_strlen(msh_ctx->s_status);
	return (i);
}

int	double_quotes_lexer(char *line, int i, t_msh *msh_ctx)
{
	while (line[++i] != '\"')
	{
		if (line[i] == '$' && line[i + 1] != ' ' && \
							line[i + 1] != '\"' && line[i + 1] != '?')
			i = pass_env_var_value_from_lexer(line, i + 1, msh_ctx);
		if (line[i] == '$' && line[i + 1] == '?')
			i = handle_status_from_lexer(i + 1, msh_ctx);
		if (line[i] == '\0')
		{
			printf("Not closed quote \"\n");
			msh_ctx->not_valid_input = 1;
			return (i);
		}
	}
	if (line[i + 1] == '\"')
		i = double_quotes_lexer(line, i + 1, msh_ctx);
	else if (line[i + 1] == '\'')
		i = single_quote_lexer(line, i + 1, msh_ctx);
	else if (line[i + 1] == '|')
		return (i);
	else if (line[i + 1] != ' ' && line[i + 1] != '\0')
		i = regular_char_lexer(line, i + 1, msh_ctx);
	return (i);
}

int	single_quote_lexer(char *line, int i, t_msh *msh_ctx)
{
	while (line[++i] != '\'')
	{
		if (line[i] == '\0')
		{
			printf("Not closed quote \'\n");
			msh_ctx->not_valid_input = 1;
			return (i);
		}
	}
	if (line[i + 1] == '\'')
		i = single_quote_lexer(line, i + 1, msh_ctx);
	else if (line[i + 1] == '\"')
		i = double_quotes_lexer(line, i + 1, msh_ctx);
	else if (line[i + 1] == '|')
		return (i);
	else if (line[i + 1] != ' ' && line[i + 1] != '\0')
		i = regular_char_lexer(line, i + 1, msh_ctx);
	return (i);
}
