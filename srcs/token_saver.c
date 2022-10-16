/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_saver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 07:39:35 by heboni            #+#    #+#             */
/*   Updated: 2022/10/16 17:54:04 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_status_from_saver(char **tokens, int t_n, int i, t_msh *msh_ctx)
{
	tokens[t_n] = ft_strcpy_end(tokens[t_n], msh_ctx->s_status);
	return (i);
}

int	double_quotes_saver_core(char **tokens, int t_n, int i, t_msh *msh_ctx)
{
	int	k;

	k = ft_strlen(tokens[t_n]) - 1;
	while ((msh_ctx->line)[++i] != '\"' && (msh_ctx->line)[i] != '\0')
	{
		if ((msh_ctx->line)[i] == '$' && (msh_ctx->line)[i + 1] != ' ' && \
			(msh_ctx->line)[i + 1] != '\"' && (msh_ctx->line)[i + 1] != '?')
		{
			i = get_env_var_value_to_saver(tokens, t_n, i + 1, msh_ctx);
			k = ft_strlen(tokens[t_n]) - 1;
		}
		else if ((msh_ctx->line)[i] == '$' && (msh_ctx->line)[i + 1] == '?')
		{
			i = handle_status_from_saver(tokens, t_n, i + 1, msh_ctx);
			k = ft_strlen(tokens[t_n]) - 1;
		}
		else
			tokens[t_n][++k] = (msh_ctx->line)[i];
	}
	tokens[t_n][++k] = '\0';
	return (i);
}

void	double_quotes_token_saver(char **tokens, int t_n, int i, t_msh *msh_ctx)
{
	i = double_quotes_saver_core(tokens, t_n, i, msh_ctx);
	if ((msh_ctx->line)[i] == '\0')
		return ;
	else if ((msh_ctx->line)[i + 1] == '\'')
		single_quote_token_saver(tokens, t_n, i + 1, msh_ctx);
	else if ((msh_ctx->line)[i + 1] == '\"')
		double_quotes_token_saver(tokens, t_n, i + 1, msh_ctx);
	else if ((msh_ctx->line)[i + 1] == '|')
		return ;
	else if ((msh_ctx->line)[i + 1] != ' ' && (msh_ctx->line)[i + 1] != '\0')
		regular_char_token_saver(tokens, t_n, i + 1, msh_ctx);
}

void	single_quote_token_saver(char **tokens, int t_n, int i, t_msh *msh_ctx)
{
	int	k;

	k = ft_strlen(tokens[t_n]) - 1;
	while ((msh_ctx->line)[++i] != '\'' && (msh_ctx->line)[i] != '\0')
		tokens[t_n][++k] = (msh_ctx->line)[i];
	tokens[t_n][++k] = '\0';
	if ((msh_ctx->line)[i + 1] == '\'')
		single_quote_token_saver(tokens, t_n, i + 1, msh_ctx);
	else if ((msh_ctx->line)[i + 1] == '\"')
		double_quotes_token_saver(tokens, t_n, i + 1, msh_ctx);
	else if ((msh_ctx->line)[i + 1] == '|')
		return ;
	else if ((msh_ctx->line)[i + 1] != ' ' && (msh_ctx->line)[i + 1] != '\0')
		regular_char_token_saver(tokens, t_n, i + 1, msh_ctx);
}

void	special_chars_token_saver(char **tokens, int t_n, char *line, int i)
{
	int	k;

	k = -1;
	tokens[t_n][++k] = line[i];
	i++;
	if ((line[i - 1] == '>' && line[i] == '>') || \
			(line[i - 1] == '<' && line[i] == '<'))
	{
		tokens[t_n][++k] = line[i];
		i++;
	}
	tokens[t_n][++k] = '\0';
}
