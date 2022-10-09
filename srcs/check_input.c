/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 08:40:26 by heboni            #+#    #+#             */
/*   Updated: 2022/10/09 11:03:23 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_real_special_token(t_msh *msh_ctx, char **tokens, \
									int t_n, char *special_s)
{
	int	is_real;

	is_real = 0;
	if (ft_strcmp(tokens[t_n], special_s) == 0 && \
		!is_in_exception_indexes(msh_ctx, t_n))
		is_real = 1;
	return (is_real);
}

int	is_real_redirect(t_msh *msh_ctx, char **tokens, int t_i)
{
	int	is_real;

	is_real = 0;
	if (is_real_special_token(msh_ctx, tokens, t_i, ">") || \
			is_real_special_token(msh_ctx, tokens, t_i, ">>") || \
			is_real_special_token(msh_ctx, tokens, t_i, "<") || \
			is_real_special_token(msh_ctx, tokens, t_i, "<<"))
		is_real = 1;
	return (is_real);
}

int	pipe_is_first_or_last(char **tokens, int t_count, t_msh *msh_ctx)
{
	int	is;

	is = 0;
	if (is_real_special_token(msh_ctx, tokens, 0, "|") || \
			is_real_special_token(msh_ctx, tokens, t_count - 1, "|"))
	{
		ft_putstr_fd("bash: syntax error near unexpected token \'|\'\n", 2);
		msh_ctx->not_valid_input = 1;
		is = 1;
	}
	return (is);
}

int	no_regular_after_redirect(t_msh *msh_ctx, char **tokens, \
											int t_count, int t_i)
{
	if (is_real_redirect(msh_ctx, tokens, t_i))
	{
		if (t_i + 1 == t_count)
		{
			ft_putstr_fd("bash: syntax error near unexpected \
										token \'newline\'\n", 2);
			msh_ctx->not_valid_input = 1;
			return (1);
		}
		if (is_special_token(tokens, t_i + 1, msh_ctx))
		{
			ft_putstr_fd("bash: syntax error near unexpected token \'>\'\n", 2);
			msh_ctx->not_valid_input = 1;
			return (1);
		}
	}
	return (0);
}

void	check_valid_input(char **tokens, int t_count, t_msh *msh_ctx)
{
	int	i;

	i = -1;
	if (pipe_is_first_or_last(tokens, t_count, msh_ctx))
		return ;
	while (++i < t_count)
	{
		if (i > 0)
		{
			if (is_real_special_token(msh_ctx, tokens, i, "|") && \
					is_real_special_token(msh_ctx, tokens, i - 1, "|"))
			{
				ft_putstr_fd("bash: syntax error near unexpected \
													token \'|\'\n", 2);
				msh_ctx->not_valid_input = 1;
				return ;
			}
		}
		if (no_regular_after_redirect(msh_ctx, tokens, t_count, i))
			return ;
	}
}
