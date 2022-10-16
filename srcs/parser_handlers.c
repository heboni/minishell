/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:54:38 by heboni            #+#    #+#             */
/*   Updated: 2022/10/16 19:21:57 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tmp_i = i; //"
int	double_quotes_token_handler(int i, t_msh *msh_ctx, int *toks_count)
{
	int	tmp_i;
	int	token_len;

	tmp_i = i;
	i = double_quotes_lexer(msh_ctx->line, i, msh_ctx);
	token_len = i - tmp_i + msh_ctx->cur_env_vars_len;
	if (token_len != 0)
	{
		(*toks_count)++;
		if (is_exeption_token(msh_ctx->line, tmp_i, '\"'))
		{
			msh_ctx->exeption_indxs = int_array_realloc(\
					&(msh_ctx->exeption_indxs), &(msh_ctx->exeption_indxs_n));
			(msh_ctx->exeption_indxs)[msh_ctx->exeption_indxs_n - 1] = \
															(*toks_count) - 1;
		}
		msh_ctx->tokens = tokens_realloc(msh_ctx->tokens, *toks_count);
		msh_ctx->tokens[*toks_count - 1] = alloc(token_len);
		double_quotes_token_saver(msh_ctx->tokens, (*toks_count) - 1, \
															tmp_i, msh_ctx);
		msh_ctx->tokens[*toks_count - 1][token_len] = '\0';
	}
	return (i);
}

// tmp_i = i; //'
int	single_quote_token_handler(int i, t_msh *msh_ctx, int *toks_count)
{
	int	tmp_i;
	int	token_len;

	tmp_i = i;
	i = single_quote_lexer(msh_ctx->line, i, msh_ctx);
	token_len = i - tmp_i + msh_ctx->cur_env_vars_len;
	(*toks_count)++;
	if (is_exeption_token(msh_ctx->line, tmp_i, '\''))
	{
		msh_ctx->exeption_indxs = int_array_realloc(\
			&(msh_ctx->exeption_indxs), &(msh_ctx->exeption_indxs_n));
		(msh_ctx->exeption_indxs)[msh_ctx->exeption_indxs_n - 1] = \
															*toks_count - 1;
	}
	msh_ctx->tokens = tokens_realloc(msh_ctx->tokens, *toks_count);
	msh_ctx->tokens[*toks_count - 1] = alloc(token_len);
	single_quote_token_saver(msh_ctx->tokens, *toks_count - 1, tmp_i, msh_ctx);
	msh_ctx->tokens[*toks_count - 1][token_len] = '\0';
	return (i);
}

int	special_chars_token_handler(int i, t_msh *msh_ctx, int *toks_count)
{
	int	tmp_i;
	int	token_len;

	tmp_i = i;
	i = special_chars_lexer(msh_ctx->line, i);
	token_len = i - tmp_i;
	(*toks_count)++;
	i--;
	msh_ctx->tokens = tokens_realloc(msh_ctx->tokens, *toks_count);
	msh_ctx->tokens[*toks_count - 1] = alloc(token_len);
	special_chars_token_saver(msh_ctx->tokens, *toks_count - 1, \
											msh_ctx->line, tmp_i);
	msh_ctx->tokens[*toks_count - 1][token_len] = '\0';
	return (i);
}

int	regular_chars_token_handler(int i, t_msh *msh_ctx, int *toks_count)
{
	int	tmp_i;
	int	token_len;

	tmp_i = i;
	i = regular_char_lexer(msh_ctx->line, i, msh_ctx);
	token_len = i - tmp_i + msh_ctx->cur_env_vars_len;
	if (token_len != 0)
	{
		(*toks_count)++;
		msh_ctx->tokens = tokens_realloc(msh_ctx->tokens, *toks_count);
		msh_ctx->tokens[*toks_count - 1] = alloc(token_len);
		regular_char_token_saver(msh_ctx->tokens, *toks_count - 1, \
														tmp_i, msh_ctx);
		msh_ctx->tokens[*toks_count - 1][token_len] = '\0';
	}
	return (i);
}

int	is_exeption_token(char *line, int tmp_i, char c)
{
	if (((line[tmp_i + 1] == '|' || line[tmp_i + 1] == '>' || \
		line[tmp_i + 1] == '<') && line[tmp_i + 2] == c && \
		(line[tmp_i + 3] == ' ' || line[tmp_i + 3] == '\0')) || \
		(((line[tmp_i + 1] == '>' && line[tmp_i + 2] == '>') || \
		(line[tmp_i + 1] == '<' && line[tmp_i + 2] == '<')) && \
		line[tmp_i + 3] == c && (line[tmp_i + 4] == ' ' || \
		line[tmp_i + 4] == '\0')))
	{
		return (1);
	}
	return (0);
}
//exeption_token
//"|" '|' "<" '<' "<<" '<<' ">" '>' ">>" '>>'