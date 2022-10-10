/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:35:10 by sotherys          #+#    #+#             */
/*   Updated: 2022/10/11 09:47:04 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_msh		*msh_ctx;
	char		*line;
	char		*prompt;

	if (argc != 1 || *(argv + 1))
		exit(INPUT_ERROR);
	
	msh_ctx = (t_msh *)malloc(sizeof(t_msh));
	if (!msh_ctx)
		exit(STACK_OVERFLOW);

	msh_ctx->env_lst = NULL;
	envs_saver(env, &msh_ctx->env_lst);
	msh_ctx->status = 0;
	msh_ctx->s_status = NULL;
	msh_ctx->heredoc_stop_f = NULL;
	prompt = get_prompt();
	while (1)
	{
		line = readline(prompt); // printf("[main] line: %s, len=%d\n", line, (int)ft_strlen(line));
		if (line && ft_strlen(line))
			add_history(line);
		if (!line)
		{
			msh_ctx->status = 0;
			break ;
		}
		msh_ctx->not_valid_input = 0;
		msh_ctx->node = parser(line, msh_ctx);
		free(line);
		if (msh_ctx->node == NULL || msh_ctx->not_valid_input == 1)
			continue;
		printf("\n[main] "); print_nodes_list(msh_ctx->node);
		executor(msh_ctx);
		free_nodes_lst(&msh_ctx->node_tmp);
		free_string_array(msh_ctx->envs);
	}
	free_env_lst(&msh_ctx->env_lst);
	if (msh_ctx->heredoc_stop_f)
		free(msh_ctx->heredoc_stop_f);
	free(prompt);
	free(msh_ctx);
	exit(0);
}
