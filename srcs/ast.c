/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:54:51 by sotherys          #+#    #+#             */
/*   Updated: 2022/10/06 22:17:29 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*ast_create_node(t_ast_type type, void *data)
{
	t_ast_node	*node;

	if (!data)
		return (NULL);
	node = (t_ast_node *) malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->fd_in = STDIN_FILENO;
	node->fd_out = STDOUT_FILENO;
	node->data = data;
	return (node);
}

void	ast_node_lst_push_bottom(t_ast_node **head, t_ast_type type)
{
	t_ast_node	*new;
	t_ast_node	*last_node;

	new = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (new == NULL)
		exit(STACK_OVERFLOW);
	new->type = type;
	new->data = NULL; //чтобы не пытался зафришить free((*ast_nodes)->data);
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return ;
	}
	last_node = get_last_ast_node(*head);
	last_node->next = new;
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

void	ast_cmd_node_lst_push_bottom(t_ast_node **head, char **tokens, int *t_i, t_ast_type type, t_msh *msh_ctx)
{
	t_ast_node	*new;
	t_ast_node	*last_node;
	t_ast_cmd	*cmd;
	// char		*path;

	new = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (new == NULL)
		exit(STACK_OVERFLOW);
	new->type = type;
	if (type == MSH_CMD)
	{
		cmd = (t_ast_cmd *)malloc(sizeof(t_ast_cmd));
		cmd->cmd_name = ft_strdup(tokens[*t_i]);
		cmd->path = NULL;
		// cmd->status_argv = fill_status_argv(tokens, t_i, msh_ctx);
		
		// path = get_cmd_path(cmd->cmd_name, msh_ctx->env);
		// if (path) //TO DO добавить в аргументы
		// 	cmd->path = path;
		new->data = cmd;
		new->fd_in = STDIN_FILENO;
		new->fd_out = STDOUT_FILENO;
		//в какой момент вместо $? подставляется статус выполнения предыдущей команды
		cmd->argv = get_cmd_node_argv(tokens, t_i, msh_ctx); //должен возвращать NULL если нет argv +
		// print_string_array(cmd->argv, 0);
	}
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

char	**get_cmd_node_argv(char **tokens, int *token_i, t_msh *msh_ctx)
{
	char	**argv;
	int		tokens_count;
	int		argv_count;
	int		tmp_i;

	(*token_i)--;
	argv_count = 0;
	argv = NULL; //тогда передадим cmd->argv NULL в env
	tmp_i = *token_i;
	tokens_count = get_tokens_count(tokens);
	// printf("[get_cmd_node_argv] *token_i = %d, tokens_count = %d\n", *token_i, tokens_count);
	while (++(*token_i) < tokens_count) //argv[0] - the name of the executed program (for example, the last component of path)
	{
		if (is_special_token(tokens, *token_i, msh_ctx->exeption_indexes, msh_ctx->exeption_indexes_n))
			break;
		argv_count++;
	}
	(*token_i)--;
	// printf("[get_cmd_node_argv] *token_i to return = %d\n", *token_i);
	// printf("[get_cmd_node_argv] argv_count = %d\n", argv_count);
	if (argv_count == 0)
		return (argv);
	argv = (char **)malloc(sizeof(char *) * (argv_count + 1));
	if (!argv)
		exit (STACK_OVERFLOW);
	
	int i = -1;
	while (++i < argv_count)
	{
		argv[i] = ft_strdup(tokens[++tmp_i]);
		// printf("[get_cmd_node_argv] argv[%d]=%s\n", i, argv[i]);
	}
	argv[i] = NULL;
	// printf("[get_cmd_node_argv] END\n");
	return (argv);
}

//токен является специальным, если он один из (|<><<>>) И token_n нет в exeption_indexes ()
int	is_special_token(char **tokens, int token_i, int *exeption_indexes, int exeption_indexes_n) 
{
	int is_special;

	is_special = 0;
	// if (!is_in_exception_indexes(exeption_indexes, exeption_indexes_n, token_i))
	// 	return (0);
	if (is_special_symbols(tokens[token_i]) && !is_in_exception_indexes(exeption_indexes, exeption_indexes_n, token_i))
		is_special = 1;
	return (is_special);
}

int	is_special_symbols(char *token)
{
	int is_special;

	is_special = 0;
	if (ft_strcmp(token, "|") == 0 || ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0 \
							|| ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">>") == 0)
		is_special = 1;
	return (is_special);
}

t_ast_node	*get_last_ast_node(t_ast_node *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	print_nodes_list(t_ast_node *ast_nodes)
{	
	t_ast_cmd *cmd;
	
	if (ast_nodes == NULL)
	{
		printf("[print_nodes_list NO_LIST]\n");
		return ;
	}
	printf("[print_nodes_list]\n");
	while (ast_nodes)
	{
		printf("type: %u ", ast_nodes->type);
		if (ast_nodes->type == MSH_PIPE)
			printf("PIPE\n");
		if (ast_nodes->type == MSH_REDIRECT_L)
			printf("MSH_REDIRECT_L: < \n");
		if (ast_nodes->type == MSH_REDIRECT_LL)
			printf("MSH_REDIRECT_LL: << \n");
		if (ast_nodes->type == MSH_REDIRECT_R)
			printf("MSH_REDIRECT_R: > \n");
		if (ast_nodes->type == MSH_REDIRECT_RR)
			printf("MSH_REDIRECT_RR: >> \n");
		if (ast_nodes->type == MSH_CMD)
		{
			if (ast_nodes->data)
			{
				cmd = ast_nodes->data;
				printf("CMD->NAME: %s\n", cmd->cmd_name);
				if (cmd->argv)
				{
					char **cmd_argv = cmd->argv;
					printf("        CMD->ARGV: ");
					while (*cmd_argv != NULL)
					{
						printf("%s, ", *cmd_argv);
						cmd_argv++;
					}
					printf("\n");
				}
				// if (cmd->status_argv)
				// {
				// 	int *status_argv = cmd->status_argv;
				// 	while (*status_argv != -100)
				// 	{
				// 		printf("%d, ", *status_argv);
				// 		status_argv++;
				// 	}
				// 	printf("\n");
				// }
			}
		}
		ast_nodes = ast_nodes->next;
	}
	printf("[print_nodes_list END]\n\n");
}
