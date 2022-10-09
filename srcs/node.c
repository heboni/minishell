/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:54:51 by sotherys          #+#    #+#             */
/*   Updated: 2022/10/09 13:49:57 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TO DO: отказаться от t_ast_type type
void	ast_cmd_node_lst_push_bottom(t_node **head, char **tokens, int *t_i, t_ast_type type, t_msh *msh_ctx)
{
	t_node	*new;
	t_node	*last_node;
	// char		*path;
	
	// printf("[ast_cmd_node_lst_push_bottom] START\n");
	new = (t_node *)malloc(sizeof(t_node));
	if (new == NULL)
		exit(STACK_OVERFLOW);
	new->type = type;
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	
	new->r_f = NULL; new->rr_f = NULL; new->l_f = NULL; new->ll_f = NULL;
	while (*t_i < msh_ctx->tokens_count && redir_token_handler(tokens, t_i, msh_ctx, new)) //отправили первый > //после выполнения этой ф уже на файле стоим
	{//переходим с файла на следующий редир, либо на команду, тогда redir_token_handler вернет 0 в след. витке
		(*t_i)++;
	}
	new->cmd_name = NULL;
	if (*t_i < msh_ctx->tokens_count)
		new->cmd_name = ft_strdup(tokens[*t_i]);
	new->path = NULL; //внутри сделать проверку, if (new->cmd_name == NULL) return (NULL);
	new->argv = get_cmd_node_argv(tokens, t_i, msh_ctx, new); //должен возвращать NULL если нет argv +
	//если встретили редирект, вызывает фу-ю обработки редиректа (вынести верхнее туда)
	//до формирования cmd_name также надо вызвать тк команда мб "> file4 echo abc"
	
	new->next = NULL;
	if (!*head)
	{
		*head = new; // printf("[ast_cmd_node_lst_push_bottom] END\n\n");
		return ;
	}
	
	last_node = get_last_ast_node(*head);
	last_node->next = new;
	// printf("[ast_cmd_node_lst_push_bottom] END\n\n");
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
		while (++tmp_i < msh_ctx->tokens_count && redir_token_handler(tokens, &tmp_i, msh_ctx, new)) {}
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

int *fill_status_argv(char **tokens, int *t_i, t_msh *msh_ctx)
{
	int	*status_argv; //хранит индексы аргументов в cmd->argv (не токенов в tokens), которые являются $? (значением статуса)
	int	status_count;
	int	i;
	int j;
	int token_i;

	i = -1;
	status_count = 0;
	status_argv = NULL;
	while (++i < msh_ctx->exeption_indexes_n)
	{
		token_i = msh_ctx->exeption_indexes[i];
		if (token_i > *t_i) //*t_i - индекс имени команды
		{
			if (ft_strcmp(tokens[token_i], "$?"))
				status_count++;
		}
	}
	if (status_count == 0)
		return (NULL);
	status_argv = (int *)malloc(sizeof(int) * (status_count + 1));
	if (!status_argv)
		exit (STACK_OVERFLOW);
	i = -1;
	j = 0;
	while (++i < msh_ctx->exeption_indexes_n)
	{
		token_i = msh_ctx->exeption_indexes[i];
		if (token_i > *t_i) //*t_i - индекс имени команды
		{
			if (ft_strcmp(tokens[token_i], "$?"))
			{
				status_argv[j] = token_i - *t_i - 1;
				j++;
			}	
		}
	}
	status_argv[++j] = -100;
	return (status_argv);
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
		printf("type: %u ", node->type);
		if (node->type == MSH_CMD)
		{
			printf("CMD->NAME: %s\n", node->cmd_name);
			printf("        r_f: %s\n", node->r_f);
			printf("        rr_f: %s\n", node->rr_f);
			printf("        l_f: %s\n", node->l_f);
			printf("        ll_f: %s\n", node->ll_f);
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
		}
		node = node->next;
	}
	printf("[print_nodes_list END]\n\n");
}