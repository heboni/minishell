/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:18:30 by heboni            #+#    #+#             */
/*   Updated: 2022/10/11 13:49:25 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	status_handler(pid_t pid, t_msh *msh_ctx)
{
	int	w_status;
	int w_code;
	
	waitpid(pid, &w_status, 0);
	if (WIFEXITED(w_status))
	{
		w_code = WEXITSTATUS(w_status);
		msh_ctx->status = w_code;
		// if (w_code != 0 )
		// {
		// 	ft_putstr_fd("\nFAILURE with wait_status_code\n", 2);
		// 	printf("w_status=%d,  w_code %d\n", w_status, w_code);
		// }
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
		ms_write_heredoc_file(msh_ctx);
		if (msh_ctx->is_stdin_pipe) //сперва pipe, потом redir, так как выигрывают fd редиректа
			dup2(msh_ctx->p_r, 0); //0 указывает на read end pipe
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
			exec_builtins(msh_ctx);
			exit(msh_ctx->status); //так смогу не exit'аться из одиночных команд (не вызывать exit в самом buitin)
			// и с правильным кодом exit'аться из форкнутого процесса 
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
		status_handler(pid, msh_ctx);
	}	
}


void	exec_builtins(t_msh *msh_ctx)
{
	// printf("BUILTIN!!");
	if (ft_strcmp(msh_ctx->node->cmd_name, "exit") == 0)
		msh_ctx->status = exit_builtin(msh_ctx);
	else if (ft_strcmp(msh_ctx->node->cmd_name, "pwd") == 0)
		msh_ctx->status = pwd_builtin(msh_ctx);
	else if (ft_strcmp(msh_ctx->node->cmd_name, "echo") == 0)
		echo_builtin(msh_ctx);
	// else if (ft_strcmp(msh_ctx->node->cmd_name, "cd") == 0)
	// 	ms_cmd_execute_exit(msh_ctx);
	// else if (ft_strcmp(msh_ctx->node->cmd_name, "export") == 0)
	// 	ft_export(msh_ctx);
	// else if (ft_strcmp(msh_ctx->node->cmd_name, "unset") == 0)
	// 	ft_unset(msh_ctx);
	// else if (ft_strcmp(msh_ctx->node->cmd_name, "env") == 0)
	// 	ft_echo(msh_ctx);
}

int	is_builtin(char *cmd_name)
{
	int	is_builtin;
	
	is_builtin = 0;
	if (ft_strcmp(cmd_name, "cd") == 0) //
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
	msh_ctx->envs = envs_lst_to_char_array(msh_ctx->env_lst); // print_string_array(msh_ctx->envs, 0);
	if (!msh_ctx->node->next)
	{
		if (is_builtin(msh_ctx->node->cmd_name))
			exec_builtins(msh_ctx);
		else
			one_cmd_executor(msh_ctx);
	}
	else
		pipes_executor(msh_ctx);
}


	// 	if (pipe(pipefd) == -1)
	// 	{
	// 		ft_putstr_fd_nl("Pipe error: ", strerror(errno), 2);
	// 		msh_ctx->status = errno;
	// 		return ;
	// 	}
