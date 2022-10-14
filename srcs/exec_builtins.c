/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:28:45 by heboni            #+#    #+#             */
/*   Updated: 2022/10/14 15:57:07 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd_name)
{
	int	is_builtin;

	is_builtin = 0;
	if (ft_strcmp(cmd_name, "cd") == 0)
		is_builtin = 1;
	else if (ft_strcmp(cmd_name, "exit") == 0)
		is_builtin = 1;
	else if (ft_strcmp(cmd_name, "echo") == 0)
		is_builtin = 1;
	else if (ft_strcmp(cmd_name, "export") == 0)
		is_builtin = 1;
	else if (ft_strcmp(cmd_name, "unset") == 0)
		is_builtin = 1;
	else if (ft_strcmp(cmd_name, "echo") == 0)
		is_builtin = 1;
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		is_builtin = 1;
	return (is_builtin);
}

void	proxy_to_builtins(t_msh *msh_ctx)
{
	if (ft_strcmp(msh_ctx->node->cmd_name, "exit") == 0)
		msh_ctx->status = exit_builtin(msh_ctx);
	else if (ft_strcmp(msh_ctx->node->cmd_name, "pwd") == 0)
		msh_ctx->status = pwd_builtin(msh_ctx);
	else if (ft_strcmp(msh_ctx->node->cmd_name, "echo") == 0)
		msh_ctx->status = echo_builtin(msh_ctx);
	else if (ft_strcmp(msh_ctx->node->cmd_name, "cd") == 0)
		msh_ctx->status = cd_builtin(msh_ctx);
	else if (ft_strcmp(msh_ctx->node->cmd_name, "env") == 0)
		msh_ctx->status = env_builtin(msh_ctx);
	else if (ft_strcmp(msh_ctx->node->cmd_name, "export") == 0)
		msh_ctx->status = export_builtin(msh_ctx);
	else if (ft_strcmp(msh_ctx->node->cmd_name, "unset") == 0)
		msh_ctx->status = unset_builtin(msh_ctx);
}

void	exec_builtin(t_msh *msh_ctx)
{
	int	tmp_in;
	int	tmp_out;

	if (msh_ctx->node->cmd_status != 0)
		return ;
	ms_write_heredoc_file(msh_ctx);
	tmp_in = dup(0);
	tmp_out = dup(1);
	if (msh_ctx->node->fd_out != 1)
	{
		dup2(msh_ctx->node->fd_out, 1);
		close(msh_ctx->node->fd_out);
	}
	if (msh_ctx->node->fd_in != 0)
	{
		dup2(msh_ctx->node->fd_in, 0);
		close(msh_ctx->node->fd_in);
	}
	proxy_to_builtins(msh_ctx);
	dup2(tmp_out, 1);
	close(tmp_out);
	dup2(tmp_in, 0);
	close(tmp_in);
}
