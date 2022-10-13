/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_node.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:35:27 by sotherys          #+#    #+#             */
/*   Updated: 2022/10/13 07:55:49 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_AST_H
# define MSH_AST_H

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

//cmd_status: если != 0, не выполнять cmd
typedef struct s_node
{
	t_redirect_type	type;  //TO DO delete
	int			fd_in;
	int			fd_out;
	int			cmd_status;
	char		*cmd_name;
	char		*path;
	char		**argv;
	int			argv_count;
	char		*r_f;
	char		*rr_f;
	char		*l_f;
	char		*ll_f;
	struct s_node	*next;
}				t_node;

#endif
