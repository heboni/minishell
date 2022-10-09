/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:35:27 by sotherys          #+#    #+#             */
/*   Updated: 2022/10/08 09:37:21 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_AST_H
# define MSH_AST_H

# include "btree.h"

typedef enum s_ast_type
{
	MSH_PIPE,
	MSH_CMD,
	MSH_REDIRECT_R, //>
	MSH_REDIRECT_RR,
	MSH_REDIRECT_L, //<
	MSH_REDIRECT_LL,
	MSH_AST_TYPE_END
}				t_ast_type;

# define MSH_AST_TYPE_CNT MSH_AST_TYPE_END

typedef struct s_node
{
	t_ast_type	type;  //TO DO delete
	int			fd_in; //изначально инициировать как STDIN и STDOUT //если в ноде есть редиректы, то заменять
	int			fd_out;
	char		*cmd_name;
	char		*path;
	char		**argv;
	char		*r_f;
	char		*rr_f;
	char		*l_f;
	char		*ll_f;
	void		*data; //TO DO delete
	struct s_node	*next;
}				t_node;

typedef struct s_ast_pipe
{
	int	pipefd[2];
}				t_ast_pipe;

typedef struct s_ast_cmd
{
	char	*cmd_name;
	char	*path;
	char	**argv;
	int		*status_argv; //можно тут хранить индексы аргументов, которые являются $? "$?"
}				t_ast_cmd;

void		ast_exec(t_btree *root);
void		ast_exec_node(t_btree *node);
void		dup_check(int fd, int oldfd);
void		close_check(int fd);
t_node	*ast_create_node(t_ast_type type, void *data);

#endif
