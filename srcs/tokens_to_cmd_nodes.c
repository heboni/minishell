/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmd_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 22:32:22 by heboni            #+#    #+#             */
/*   Updated: 2022/10/12 22:46:47 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*tokens_to_ast_nodes(char **tokens, int toks_count, t_msh *msh_ctx)
{
	int		token_i;
	t_node	*ast_nodes;

	token_i = -1;
	ast_nodes = NULL;
	while (++token_i < toks_count)
	{
		if (ft_strcmp(tokens[token_i], "|") == 0 && \
				!is_in_exception_indexes(msh_ctx, token_i))
			continue ;
		else
			node_lst_push_bottom(&ast_nodes, tokens, &token_i, msh_ctx);
	}
	return (ast_nodes);
}

//is_in_exception_indexes - если его порядковый номер внесен в exeption_indxs, 
//т.е. он является одним из "|" '|' "<" '<' "<<" '<<' ">" '>' ">>" '>>'
int	is_in_exception_indexes(t_msh *msh_ctx, int token_i)
{
	int	i;
	int	is_in_exception_indexes;

	i = -1;
	is_in_exception_indexes = 0;
	while (++i < msh_ctx->exeption_indxs_n)
	{
		if (token_i == msh_ctx->exeption_indxs[i])
		{
			is_in_exception_indexes = 1;
			break ;
		}
	}
	return (is_in_exception_indexes);
}
