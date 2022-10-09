/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:35:10 by sotherys          #+#    #+#             */
/*   Updated: 2022/10/09 13:24:07 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_msh		*msh_ctx;
	char		*line;
	char		*prompt;

	if (argc != 1)
		exit(INPUT_ERROR);
	argv = NULL;
	
	msh_ctx = (t_msh *)malloc(sizeof(t_msh));
	if (!msh_ctx)
		exit(STACK_OVERFLOW);

	msh_ctx->env = NULL;
	envs_saver(env, &msh_ctx->env);	
	
	prompt = get_prompt();
	while (1)
	{
		line = readline(prompt); // printf("[main] line: %s\n", line);
		if (line && ft_strlen(line))
			add_history(line);
		if (!line)
			break ;
		msh_ctx->status = 0;
		msh_ctx->not_valid_input = 0;
		msh_ctx->node = parser(line, msh_ctx);
		free(line);
		if (msh_ctx->node == NULL || msh_ctx->not_valid_input == 1)
			continue;
		// executor(msh_ctx);
		//когда делать шаг подготовки: создание файлов и тд //создание файлов в ast_cmd_node_lst_push_bottom
		printf("\n[main] "); print_nodes_list(msh_ctx->node);
		free_nodes_lst(&msh_ctx->node); //TO BE DONE переделать под новую стр.
	}
	free_env_lst(&msh_ctx->env);
	free(prompt);
	free(msh_ctx);
	return (0);
}
