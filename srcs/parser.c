/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 22:19:51 by heboni            #+#    #+#             */
/*   Updated: 2022/10/13 23:56:41 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parser(t_msh *msh_ctx)
{
	t_node	*ast_nodes;
	char	**tokens;

	msh_ctx->not_valid_input = 0;
	msh_ctx->exeption_indxs = NULL;
	msh_ctx->exeption_indxs_n = 0;
	tokens = get_tokens(msh_ctx->line, msh_ctx);
	if (tokens == NULL)
		return (NULL);
	msh_ctx->toks_count = get_tokens_count(tokens); printf("toks_count: %d\n", msh_ctx->toks_count);
	print_int_array(msh_ctx->exeption_indxs, msh_ctx->exeption_indxs_n); //
	check_valid_input(tokens, msh_ctx->toks_count, msh_ctx);
	if (msh_ctx->not_valid_input == 1)
	{
		msh_ctx->status = 258;
		free_from_parser(msh_ctx);
		return (NULL);
	}
	ast_nodes = tokens_to_ast_nodes(tokens, msh_ctx->toks_count, msh_ctx);
	free_from_parser(msh_ctx);
	return (ast_nodes);
}

void	free_from_parser(t_msh *msh_ctx)
{
	if (msh_ctx->exeption_indxs)
		free(msh_ctx->exeption_indxs);
	free_string_array(msh_ctx->tokens);
	free(msh_ctx->line);
}

char	**get_tokens(char *line, t_msh *msh_ctx)
{
	int		toks_count;
	int		len;
	int		i;

	i = -1;
	toks_count = 0;
	len = ft_strlen(line);
	msh_ctx->tokens = NULL;
	while (++i < len)
	{
		msh_ctx->cur_env_vars_len = 0;
		while (is_space(line[i]))
			i++;
		if (line[i] == '\"')
			i = double_quotes_token_handler(i, msh_ctx, &toks_count);
		else if (line[i] == '\'')
			i = single_quote_token_handler(i, msh_ctx, &toks_count);
		else if (line[i] == '|' || line[i] == '>' || line[i] == '<')
			i = special_chars_token_handler(i, msh_ctx, &toks_count);
		else if (line[i] != '\0')
			i = regular_chars_token_handler(i, msh_ctx, &toks_count);
	}
	return (msh_ctx->tokens);
}
