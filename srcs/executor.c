/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:18:30 by heboni            #+#    #+#             */
/*   Updated: 2022/10/15 15:59:33 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Реакция на нажатие Ctrl-"C" и Ctrl-"\" в дочернем процессе pid==0
static void	signal_while_child_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n\"Ctrl+C\" while_child was pressed\n", 1);
		rl_done = 1;
		// g_lobal_status = 130;
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", 1);
		ft_putstr_fd("\"Ctrl+\\\" while_child was pressed\n", 1);
		// g_lobal_status = 130;
	}
}

void	signal_handler(pid_t pid, t_msh *msh_ctx)
{
	int	w_status;
	int w_code;

	rl_event_hook=event;
	signal(SIGINT, signal_while_child_handler);
	signal(SIGQUIT, signal_while_child_handler);
	waitpid(pid, &w_status, 0);
	if (WIFEXITED(w_status))
	{
		w_code = WEXITSTATUS(w_status);
		msh_ctx->status = w_code;
	}
}

void	status_handler(pid_t pid, t_msh *msh_ctx)
{
	int	w_status;
	int w_code;

	waitpid(pid, &w_status, 0);
	if (WIFEXITED(w_status))
	{
		w_code = WEXITSTATUS(w_status);
		msh_ctx->status = w_code;
	}
}

void	one_cmd_executor(t_msh *msh_ctx)
{
	pid_t	pid;

	if (msh_ctx->node->cmd_status != 0)
		return ;
	rl_catch_signals = 0;
	rl_event_hook=event;
	pid = fork();
	if (pid < 0)
		ft_putstr_fd("Fork error\n", 2);
	else if (pid == 0)
	{
		printf("one_cmd_executor CHILD!!\n");
		signal_handler(0, msh_ctx);
		ms_write_heredoc_file(msh_ctx);
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
		if (is_builtin(msh_ctx->node->cmd_name))
		{
			proxy_to_builtins(msh_ctx);
			exit(msh_ctx->status);
		}
		else if (execve(msh_ctx->node->path, msh_ctx->node->argv, msh_ctx->envs) == -1)
		{
			ft_putstr_fd("Execve error: ", 2);
			ft_putstr_fd(strerror(errno), 2); 
			ft_putstr_fd("\n", 2);
			exit(-2);
		}
	}
	else
	{
		signal_handler(pid, msh_ctx);
		// status_handler(pid, msh_ctx);
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

// 	if (pipe(pipefd) == -1)
// 	{
// 		ft_putstr_fd_nl("Pipe error: ", strerror(errno), 2);
// 		msh_ctx->status = errno;
// 		return ;
// 	}
void	pipes_executor(t_msh *msh_ctx)
{
	int		fd[4];

	pipe(fd);
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
