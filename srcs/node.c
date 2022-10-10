/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:54:51 by sotherys          #+#    #+#             */
/*   Updated: 2022/10/11 09:35:22 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	node_lst_push_bottom(t_node **head, char **tokens, int *t_i, t_msh *msh_ctx)
{
	t_node	*new;
	t_node	*last_node;
	
	// printf("[node_lst_push_bottom] START\n");
	new = (t_node *)malloc(sizeof(t_node));
	if (new == NULL)
		exit(STACK_OVERFLOW);
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->cmd_status = 0;
	new->r_f = NULL; new->rr_f = NULL; new->l_f = NULL; new->ll_f = NULL;
	while (*t_i < msh_ctx->tokens_count && new->cmd_status == 0 && redir_token_handler(tokens, t_i, msh_ctx, new)) //отправили первый > //после выполнения этой ф уже на файле стоим
	{//переходим с файла на следующий редир, либо на команду, тогда redir_token_handler вернет 0 в след. витке
		(*t_i)++;
	}
	new->cmd_name = NULL;
	if (*t_i < msh_ctx->tokens_count)
		new->cmd_name = ft_strdup(tokens[*t_i]);
	new->path = get_cmd_path(new->cmd_name, msh_ctx);
	new->argv = get_cmd_node_argv(tokens, t_i, msh_ctx, new); //должен возвращать NULL если нет argv +
	//если встретили редирект, вызывает фу-ю обработки редиректа (вынести верхнее туда)
	//до формирования cmd_name также надо вызвать тк команда мб "> file4 echo abc"
	
	new->next = NULL;
	if (!*head)
	{
		*head = new; // printf("[node_lst_push_bottom] END\n\n");
		return ;
	}
	
	last_node = get_last_ast_node(*head);
	last_node->next = new;
	// printf("[node_lst_push_bottom] END\n\n");
	return ;
}

char	**get_cmd_node_argv(char **tokens, int *token_i, t_msh *msh_ctx, t_node *new)
{
	char	**argv;
	int		argv_count;
	int		t_count;
	int		tmp_i;

	(*token_i)--;
	argv_count = 0; t_count = 0;
	argv = NULL; //тогда передадим cmd->argv NULL в env
	tmp_i = *token_i;
	// printf("[get_cmd_node_argv] *token_i = %d, tokens_count = %d\n", *token_i, tokens_count);
	while (++(*token_i) < msh_ctx->tokens_count) //argv[0] - the name of the executed program (for example, the last component of path)
	{
		if (is_pipe_token(tokens, *token_i, msh_ctx))
			break;
		t_count++;
		if (is_redirect_token(tokens, *token_i, msh_ctx) ||
			is_redirect_token(tokens, *token_i - 1, msh_ctx))
			continue;
		argv_count++;
	}
	(*token_i)--;
	// printf("[get_cmd_node_argv] *token_i to return = %d\n", *token_i); // printf("[get_cmd_node_argv] argv_count = %d\n", argv_count);
	if (argv_count != 0)
	{
		argv = (char **)malloc(sizeof(char *) * (argv_count + 1));
		if (!argv)
			exit (STACK_OVERFLOW);
	}
	
	int i = 0; int j = -1;
	while (++j < t_count)
	{
		while (++tmp_i < msh_ctx->tokens_count && new->cmd_status == 0 && redir_token_handler(tokens, &tmp_i, msh_ctx, new)) {}
		//отправили первый > //после выполнения этой ф уже на файле стоим
		//переходим с файла на следующий редир, либо на команду, тогда redir_token_handler вернет 0 в след. витке
		if (argv && i < argv_count)
				argv[i++] = ft_strdup(tokens[tmp_i]);
	}
	if (argv)
		argv[i] = NULL;
	// printf("[get_cmd_node_argv] END\n");
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

void	print_nodes_list(t_node *node)
{	
	if (node == NULL)
	{
		printf("[print_nodes_list NO_LIST]\n");
		return ;
	}
	printf("[print_nodes_list]\n");
	while (node)
	{
		printf("node:   ");
		if (node->type == MSH_CMD)
		{
			printf("CMD->NAME: %s\n", node->cmd_name);
			printf("        CMD->PATH: %s\n", node->path);
			if (node->argv)
			{
				char **cmd_argv = node->argv;
				printf("        CMD->ARGV: ");
				while (*cmd_argv != NULL)
				{
					printf("%s, ", *cmd_argv);
					cmd_argv++;
				}
				printf("\n");
			}
			printf("        r_f: %s\n", node->r_f);
			printf("        rr_f: %s\n", node->rr_f);
			printf("        l_f: %s\n", node->l_f);
			printf("        ll_f: %s\n", node->ll_f);
		}
		node = node->next;
	}
	printf("[print_nodes_list END]\n\n");
}