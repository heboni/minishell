/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:18:30 by heboni            #+#    #+#             */
/*   Updated: 2022/10/16 20:10:17 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_puterror(char *s1, char *s2)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
	exit(-2);
}

void	pipe_call(int *fd)
{
	if (pipe(fd) == -1)
	{
		ft_putstr_fd_nl("Pipe error: ", strerror(errno), 2, 1);
		g_lobal_status = errno;
		exit(g_lobal_status);
	}
}

void	pre_executer(t_msh *msh_ctx, int fd_r, int fd_wr)
{
	if (msh_ctx->node->next == NULL)
	{
		msh_ctx->is_stdin_pipe = 1;
		msh_ctx->is_stdout_pipe = 0;
	}
	else
	{
		msh_ctx->is_stdin_pipe = fd_r;
		msh_ctx->is_stdout_pipe = fd_wr;
	}
}

void	pipes_executor(t_msh *msh_ctx)
{
	int		fd[4];

	pipe_call(fd);
	fd[2] = fd[0];
	fd[3] = fd[1];
	msh_ctx->p_r = 0;
	msh_ctx->p_wr = fd[3];
	pre_executer(msh_ctx, 0, 1);
	one_cmd_executor(msh_ctx);
	while (msh_ctx->node->next != NULL)
	{
		close(fd[3]);
		pipe(fd);
		fd[3] = fd[1];
		msh_ctx->node = msh_ctx->node->next;
		pre_executer(msh_ctx, 1, 1);
		msh_ctx->p_r = fd[2];
		msh_ctx->p_wr = fd[1];
		one_cmd_executor(msh_ctx);
		close(fd[2]);
		fd[2] = fd[0];
	}
	fd[2] = fd[0];
	close(fd[3]);
	close(fd[2]);
}

void	executor(t_msh *msh_ctx)
{
	msh_ctx->node_tmp = msh_ctx->node;
	msh_ctx->envs = envs_lst_to_char_array(msh_ctx->env_lst);
	if (!msh_ctx->node->next)
	{
		if (is_builtin(msh_ctx->node->cmd_name))
			exec_builtin(msh_ctx);
		else
			one_cmd_executor(msh_ctx);
	}
	else
		pipes_executor(msh_ctx);
}
