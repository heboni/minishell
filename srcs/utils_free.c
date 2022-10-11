/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 08:44:50 by heboni            #+#    #+#             */
/*   Updated: 2022/10/12 11:20:11 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node_components(t_node *node)
{
	if (node->cmd_name)
		free(node->cmd_name);
	if (node->path)
		free(node->path);
	if (node->argv)
		free_string_array(node->argv);
	if (node->r_f)
		free(node->r_f);
	if (node->rr_f)
		free(node->rr_f);
	if (node->l_f)
		free(node->l_f);
	if (node->ll_f)
		free(node->ll_f);
}

void	free_nodes_lst(t_node **node)
{
	t_node	*next;

	if (!node)
	{
		printf("[free_nodes_lst END NO AST_NODES]\n");
		return ;
	}
	while (*node)
	{
		next = (*node)->next;
		free_node_components(*node);
		free(*node);
		*node = next;
	}
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
	int	i;

	i = -1;
	if (!argv)
		return ;
	while (argv[++i])
		free(argv[i]);
	free(argv);
}
