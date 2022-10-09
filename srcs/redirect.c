/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:45:21 by heboni            #+#    #+#             */
/*   Updated: 2022/10/10 00:12:41 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_redirect_r_file(char **tokens, int *t_i, t_node *new, t_msh *msh_ctx)
{
	char	*f_name;
	int		fd;

	(*t_i)++; //переходим на имя файла
	f_name = ft_strdup(tokens[*t_i]); //printf("[get_redirect_file] f_name = %s\n", f_name);
	//когда проверять, является ли файл директорией
	
	fd = open(f_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) //статус выставлять в 1 не надо, тк если дальше пайп, правая команда будет выполняться
	{
		new->status = 1;
		msh_ctx->status = 1;
		ft_putstr_fd_nl("bash: ", f_name, 2, 0);
		ft_putstr_fd_nl(": ", strerror(errno), 2, 1);
		free(f_name);
		return (NULL);
	}
	new->fd_out = fd;
	return (f_name);
}

char	*get_redirect_rr_file(char **tokens, int *t_i, t_node *new, t_msh *msh_ctx)
{
	char	*f_name;

	(*t_i)++; //переходим на имя файла
	f_name = ft_strdup(tokens[*t_i]);
	//когда проверять, является ли файл директорией
	//открыть файл с нужными флагами
	
	int fd = open(f_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1) //статус выставлять в 1 не надо, тк если дальше пайп, правая команда будет выполняться
	{
		new->status = 1;
		msh_ctx->status = 1;
		ft_putstr_fd_nl("bash: ", f_name, 2, 0);
		ft_putstr_fd_nl(": ", strerror(errno), 2, 1);
		free(f_name);
		return (NULL);
	}
	new->fd_out = fd;
	return (f_name);
}

//точно после редиректа есть regular_token = имени файла
//в случае < (<<?) внутри сразу проверять, что этот файл есть в директории
char	*get_redirect_l_file(char **tokens, int *t_i, t_node *new, t_msh *msh_ctx)
{
	char	*f_name;

	(*t_i)++; //переходим на имя файла
	f_name = ft_strdup(tokens[*t_i]);
	//когда проверять, является ли файл директорией - open возвращает No such file or directory
	
	int fd = open(f_name, O_RDONLY);// int fd = open(f_name, O_RDONLY, 0644);
	if (fd == -1) //?статус выставлять в 1 не надо, тк если дальше пайп, правая команда будет выполняться
	{
		new->status = 1;
		msh_ctx->status = 1;
		ft_putstr_fd_nl("bash: ", f_name, 2, 0);
		ft_putstr_fd_nl(": ", strerror(errno), 2, 1);
		free(f_name);
		return (NULL);
	}
	new->fd_in = fd;
	return (f_name);
}

char	*get_redirect_ll_file(char **tokens, int *t_i, t_node *new, t_msh *msh_ctx) //TO BE DONE
{
	char	*f_name;

	(*t_i)++; //переходим на имя файла
	f_name = ft_strdup(tokens[*t_i]);
	new->fd_in = 0; new->fd_out = 1; //поменять в зависимости от типа
	msh_ctx->status = 0;
	//TO BE DONE
	return (f_name);
}

int	redir_token_handler(char **tokens, int *t_i, t_msh *msh_ctx, t_node *new)
{ //может мне не нужно сохранять список файлов, сразу открывать его и возвращать наиболее актуальный
	
	if (ft_strcmp(tokens[*t_i], ">") == 0 && !is_in_exception_indexes(msh_ctx, *t_i))
	{
		if (new->r_f)
			free(new->r_f); //new->r_f = NULL; 
		new->r_f = get_redirect_r_file(tokens, t_i, new, msh_ctx);
	}
	else if (ft_strcmp(tokens[*t_i], ">>") == 0 && !is_in_exception_indexes(msh_ctx, *t_i))
	{
		if (new->rr_f)
			free(new->rr_f);
		new->rr_f = get_redirect_rr_file(tokens, t_i, new, msh_ctx);
	}
	else if (ft_strcmp(tokens[*t_i], "<") == 0 && !is_in_exception_indexes(msh_ctx, *t_i))
	{
		if (new->l_f)
			free(new->l_f);
		new->l_f = get_redirect_l_file(tokens, t_i, new, msh_ctx);
	}
	else if (ft_strcmp(tokens[*t_i], "<<") == 0 && !is_in_exception_indexes(msh_ctx, *t_i))
	{
		if (new->ll_f)
			free(new->ll_f);
		new->ll_f = get_redirect_ll_file(tokens, t_i, new, msh_ctx); //TO BE DONE
	}
	else
		return (0);
	return (1);
}