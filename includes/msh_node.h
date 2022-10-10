/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_node.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:35:27 by sotherys          #+#    #+#             */
/*   Updated: 2022/10/11 09:33:43 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_AST_H
# define MSH_AST_H

# include "btree.h"

typedef enum s_redirect_type
{
	MSH_CMD,
	MSH_REDIRECT_R, //>
	MSH_REDIRECT_RR,
	MSH_REDIRECT_L, //<
	MSH_REDIRECT_LL,
	MSH_TYPE_END
}				t_redirect_type;

# define MSH_TYPE_CNT MSH_TYPE_END

typedef struct s_node
{
	t_redirect_type	type;  //TO DO delete
	int			fd_in; //изначально инициировать как STDIN и STDOUT //если в ноде есть редиректы, то заменять
	int			fd_out;
	int			cmd_status; //если != 0, не выполнять cmd
	char		*cmd_name;
	char		*path;
	char		**argv;
	char		*r_f;
	char		*rr_f;
	char		*l_f;
	char		*ll_f;
	struct s_node	*next;
}				t_node;


//TO DO delete
void		ast_exec(t_btree *root);
void		ast_exec_node(t_btree *node);
void		dup_check(int fd, int oldfd);
void		close_check(int fd);
t_node		*ast_create_node(t_redirect_type type, void *data);

#endif
