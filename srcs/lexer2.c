/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 02:07:53 by heboni            #+#    #+#             */
/*   Updated: 2022/10/14 02:08:20 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	regular_char_lexer_part(char *line, int i, t_msh *msh_ctx)
{
	if (line[i] == '\'')
	{
		i = single_quote_lexer(line, i, msh_ctx);
		if (line[i] == '\'')
			i++;
		if (line[i] == '\"')
			i++;
	}
	if (line[i] == '\"')
	{
		i = double_quotes_lexer(line, i, msh_ctx);
		if (line[i] == '\"')
			i++;
	}
	return (i);
}

int	regular_char_lexer(char *line, int i, t_msh *msh_ctx)
{
	while (1)
	{
		i = regular_char_lexer_part(line, i, msh_ctx);
		if (line[i] == '$' && line[i + 1] != ' ' && \
						line[i + 1] != '\0' && line[i + 1] != '?')
		{
			i = pass_env_var_value_from_lexer(line, i + 1, msh_ctx);
			i++;
			continue ;
		}
		if (line[i] == '$' && line[i + 1] == '?')
			i = handle_status_from_lexer(i + 1, msh_ctx);
		if (line[i] == ' ')
			break ;
		if (line[i] == '\0')
			break ;
		if (line[i] == '|' || line[i + 1] == '|' || line[i] == '>' || \
				line[i + 1] == '>' || line[i] == '<' || line[i + 1] == '<')
			break ;
		i++;
	}
	return (i);
}
