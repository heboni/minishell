/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 08:44:50 by heboni            #+#    #+#             */
/*   Updated: 2022/10/09 23:56:58 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_nodes_lst(t_node **node)
{
	t_node *next;
	
	// printf("[free_nodes_lst]\n");
	if (!node)
	{
		printf("[free_nodes_lst END NO AST_NODES]\n");
		return ;
	}
	while (*node)
	{
		next = (*node)->next;
		if ((*node)->cmd_name)
		{
			free((*node)->cmd_name); //printf("free cmd_name\n");
		}
		if ((*node)->path)
		{
			free((*node)->path); //printf("free cmd->path\n");
		}
		if ((*node)->argv)
		{
			free_string_array((*node)->argv); //printf("free cmd->argv\n");
		}
		if ((*node)->r_f)
			free((*node)->r_f);
		if ((*node)->rr_f)
			free((*node)->rr_f);
		if ((*node)->l_f)
			free((*node)->l_f);
		if ((*node)->ll_f)
			free((*node)->ll_f);
		free(*node); //printf("free *node\n");
		*node = next;
	}
	// printf("[free_nodes_lst END]\n");
}

void	lstclear(t_node **lst)
{
	t_node	*next;

	if (!lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		free(((*lst)));
		*lst = next;
	}
}

void	free_string_array(char **argv)
{
	int	i = -1;

	if (!argv)
		return ;
	while (argv[++i]) //TO DO в get_cmd_node_argv выделила память на элемент (char *)==NULL в конце, тут, получается не фришу этот указатель, утечек при этом нет
		free(argv[i]);
	free(argv);
}
