/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:45:21 by heboni            #+#    #+#             */
/*   Updated: 2022/10/16 19:10:58 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_redirect_r_file(int *t_i, t_node *new, t_msh *msh_ctx)
{
	char	*f_name;
	int		fd;

	if (new->r_f)
		free(new->r_f);
	(*t_i)++;
	f_name = NULL;
	f_name = ft_strdup((msh_ctx->tokens)[*t_i]);
	fd = open(f_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		new->cmd_status = 1;
		g_lobal_status = 1;
		ft_putstr_fd_nl("bash: ", f_name, 2, 0);
		ft_putstr_fd_nl(": ", strerror(errno), 2, 1);
		free(f_name);
		return (NULL);
	}
	msh_ctx->heredoc_fd = fd;
	new->fd_out = fd;
	return (f_name);
}

char	*get_redirect_rr_file(int *t_i, t_node *new, t_msh *msh_ctx)
{
	char	*f_name;
	int		fd;

	if (new->rr_f)
		free(new->rr_f);
	(*t_i)++;
	f_name = NULL;
	f_name = ft_strdup((msh_ctx->tokens)[*t_i]);
	fd = open(f_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		new->cmd_status = 1;
		g_lobal_status = 1;
		ft_putstr_fd_nl("bash: ", f_name, 2, 0);
		ft_putstr_fd_nl(": ", strerror(errno), 2, 1);
		free(f_name);
		return (NULL);
	}
	msh_ctx->heredoc_fd = fd;
	new->fd_out = fd;
	return (f_name);
}

//в этой функции после редиректа точно есть regular_token = имени файла
char	*get_redirect_l_file(int *t_i, t_node *new, t_msh *msh_ctx)
{
	char	*f_name;
	int		fd;

	if (new->l_f)
		free(new->l_f);
	(*t_i)++;
	f_name = NULL;
	f_name = ft_strdup((msh_ctx->tokens)[*t_i]);
	fd = open(f_name, O_RDONLY);
	if (fd == -1)
	{
		new->cmd_status = 1;
		g_lobal_status = 1;
		ft_putstr_fd_nl("bash: ", f_name, 2, 0);
		ft_putstr_fd_nl(": ", strerror(errno), 2, 1);
		free(f_name);
		return (NULL);
	}
	new->fd_in = fd;
	return (f_name);
}

char	*get_redirect_ll_file(int *t_i, t_node *new, t_msh *msh_ctx)
{
	char	*f_name;
	int		fd;

	if (new->ll_f)
		free(new->ll_f);
	(*t_i)++;
	f_name = NULL;
	f_name = ft_strdup((msh_ctx->tokens)[*t_i]);
	if (msh_ctx->heredoc_stop_f)
		free(msh_ctx->heredoc_stop_f);
	msh_ctx->heredoc_stop_f = NULL;
	msh_ctx->heredoc_stop_f = ft_strdup(f_name);
	fd = open(".del", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		new->cmd_status = 1;
		g_lobal_status = 1;
		ft_putstr_fd_nl("bash: ", f_name, 2, 0);
		ft_putstr_fd_nl(": ", strerror(errno), 2, 1);
		free(f_name);
		return (NULL);
	}
	msh_ctx->heredoc_fd = fd;
	new->fd_in = fd;
	return (f_name);
}

int	redir_token_handler(char **tokens, int *t_i, t_msh *msh_ctx, t_node *new)
{
	if (ft_strcmp(tokens[*t_i], ">") == 0 && \
					!is_in_exception_indexes(msh_ctx, *t_i))
		new->r_f = get_redirect_r_file(t_i, new, msh_ctx);
	else if (ft_strcmp(tokens[*t_i], ">>") == 0 && \
					!is_in_exception_indexes(msh_ctx, *t_i))
		new->rr_f = get_redirect_rr_file(t_i, new, msh_ctx);
	else if (ft_strcmp(tokens[*t_i], "<") == 0 && \
					!is_in_exception_indexes(msh_ctx, *t_i))
		new->l_f = get_redirect_l_file(t_i, new, msh_ctx);
	else if (ft_strcmp(tokens[*t_i], "<<") == 0 && \
					!is_in_exception_indexes(msh_ctx, *t_i))
		new->ll_f = get_redirect_ll_file(t_i, new, msh_ctx);
	else
		return (0);
	return (1);
}
