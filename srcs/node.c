/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:54:51 by sotherys          #+#    #+#             */
/*   Updated: 2022/10/16 20:09:42 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*init_cmd_node(void)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (new == NULL)
		exit(STACK_OVERFLOW);
	new->cmd_name = NULL;
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->cmd_status = 0;
	new->r_f = NULL;
	new->rr_f = NULL;
	new->l_f = NULL;
	new->ll_f = NULL;
	return (new);
}

void	node_lst_push_bottom(t_node **head, char **tokens, \
										int *t_i, t_msh *msh_ctx)
{
	t_node	*new;
	t_node	*last_node;

	new = init_cmd_node();
	while (*t_i < msh_ctx->toks_count && new->cmd_status == 0 && \
					redir_token_handler(tokens, t_i, msh_ctx, new))
		(*t_i)++;
	if (*t_i < msh_ctx->toks_count)
		new->cmd_name = ft_strdup(tokens[*t_i]);
	new->path = get_cmd_path(new->cmd_name, msh_ctx);
	new->argv = get_node_argv(tokens, t_i, msh_ctx, new);
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return ;
	}
	last_node = get_last_ast_node(*head);
	last_node->next = new;
	return ;
}

char	**fill_node_argv(int t_count, int tmp_i, t_msh *msh_ctx, t_node *new)
{
	char	**argv;
	int		i;
	int		j;

	i = 0;
	j = -1;
	argv = NULL;
	if (new->argv_count != 0)
	{
		argv = (char **)malloc(sizeof(char *) * (new->argv_count + 1));
		if (!argv)
			exit (STACK_OVERFLOW);
	}
	while (++j < t_count)
	{
		while (++tmp_i < msh_ctx->toks_count && new->cmd_status == 0 && \
				redir_token_handler(msh_ctx->tokens, &tmp_i, msh_ctx, new))
		{
		}
		if (argv && i < new->argv_count)
				argv[i++] = ft_strdup(msh_ctx->tokens[tmp_i]);
	}
	if (argv)
		argv[i] = NULL;
	return (argv);
}

//argv[0] - the name of the executed program 
//(for example, the last component of path)
char	**get_node_argv(char **tokens, int *t_i, t_msh *msh_ctx, t_node *new)
{
	char	**argv;
	int		t_count;
	int		tmp_i;

	(*t_i)--;
	new->argv_count = 0;
	t_count = 0;
	tmp_i = *t_i;
	while (++(*t_i) < msh_ctx->toks_count)
	{
		if (is_pipe_token(tokens, *t_i, msh_ctx))
			break ;
		t_count++;
		if (is_redirect_token(tokens, *t_i, msh_ctx) || \
			is_redirect_token(tokens, *t_i - 1, msh_ctx))
			continue ;
		new->argv_count++;
	}
	(*t_i)--;
	argv = fill_node_argv(t_count, tmp_i, msh_ctx, new);
	return (argv);
}

t_node	*get_last_ast_node(t_node *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

// void	print_nodes_list(t_node *node)
// {	
// 	if (node == NULL)
// 	{
// 		printf("[print_nodes_list NO_LIST]\n");
// 		return ;
// 	}
// 	printf("[print_nodes_list]\n");
// 	while (node)
// 	{
// 		printf("node:   ");
// 		printf("CMD->NAME: %s\n", node->cmd_name);
// 			printf("        CMD->PATH: %s\n", node->path);
// 			if (node->argv)
// 			{
// 				char **cmd_argv = node->argv;
// 				printf("        CMD->ARGV: ");
// 				while (*cmd_argv != NULL)
// 				{
// 					printf("%s, ", *cmd_argv);
// 					cmd_argv++;
// 				}
// 				printf("\n");
// 			}
// 			printf("        r_f: %s\n", node->r_f);
// 			printf("        rr_f: %s\n", node->rr_f);
// 			printf("        l_f: %s\n", node->l_f);
// 			printf("        ll_f: %s\n", node->ll_f);
// 		node = node->next;
// 	}
// 	printf("[print_nodes_list END]\n\n");
// }