/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 19:38:13 by heboni            #+#    #+#             */
/*   Updated: 2022/10/16 20:03:39 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(pid_t pid)
{
	int	w_status;
	int	w_code;

	signal(SIGINT, signal_while_child_handler);
	signal(SIGQUIT, signal_while_child_handler);
	waitpid(pid, &w_status, 0);
	if (WIFEXITED(w_status))
	{
		w_code = WEXITSTATUS(w_status);
		g_lobal_status = w_code;
	}
}

void	one_cmd_executor_core(t_msh *msh_ctx)
{
	if (msh_ctx->is_stdin_pipe)
		dup2(msh_ctx->p_r, 0);
	if (msh_ctx->is_stdout_pipe)
		dup2(msh_ctx->p_wr, 1);
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
}

void	one_cmd_executor(t_msh *msh_ctx)
{
	pid_t	pid;

	if (msh_ctx->node->cmd_status != 0)
		return ;
	pid = fork();
	if (pid < 0)
		ft_putstr_fd("Fork error\n", 2);
	else if (pid == 0)
	{
		signal_handler(0);
		ms_write_heredoc_file(msh_ctx);
		one_cmd_executor_core(msh_ctx);
		if (is_builtin(msh_ctx->node->cmd_name))
		{
			proxy_to_builtins(msh_ctx);
			exit(g_lobal_status);
		}
		else if (execve(msh_ctx->node->path, msh_ctx->node->argv, \
													msh_ctx->envs) == -1)
			ft_puterror("error: cannot execute ", msh_ctx->node->argv[0]);
	}
	else
		signal_handler(pid);
}
