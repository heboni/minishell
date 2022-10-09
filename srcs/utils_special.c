/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:19:21 by heboni            #+#    #+#             */
/*   Updated: 2022/10/09 13:19:48 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect_symbols(char *token)
{
	int is_redirect;

	is_redirect = 0;
	if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0 \
				|| ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">>") == 0)
		is_redirect = 1;
	return (is_redirect);
}

int	is_redirect_token(char **tokens, int t_i, t_msh *msh_ctx) 
{
	int is_redirect;

	is_redirect = 0;
	if (t_i < 0)
		return (is_redirect);
	if (is_redirect_symbols(tokens[t_i]) && !is_in_exception_indexes(msh_ctx, t_i))
		is_redirect = 1;
	return (is_redirect);
}

int	is_pipe_token(char **tokens, int t_i, t_msh *msh_ctx) 
{
	int is_pipe;

	is_pipe = 0;
	if (ft_strcmp(tokens[t_i], "|") == 0 && !is_in_exception_indexes(msh_ctx, t_i))
		is_pipe = 1;
	return (is_pipe);
}

//токен является специальным, если он один из (|<><<>>) И token_n нет в exeption_indexes ()
int	is_special_token(char **tokens, int t_i, t_msh *msh_ctx) 
{
	int is_special;

	is_special = 0;
	if (is_special_symbols(tokens[t_i]) && \
		!is_in_exception_indexes(msh_ctx, t_i))
		is_special = 1;
	return (is_special);
}

int	is_special_symbols(char *token)
{
	int is_special;

	is_special = 0;
	if (ft_strcmp(token, "|") == 0 || ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0 \
							|| ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">>") == 0)
		is_special = 1;
	return (is_special);
}
