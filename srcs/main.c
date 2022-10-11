/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:35:10 by sotherys          #+#    #+#             */
/*   Updated: 2022/10/12 11:19:36 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_msh	*msh_ctx_init(char **env)
{
	t_msh	*msh_ctx;
	
	msh_ctx = (t_msh *)malloc(sizeof(t_msh));
	if (!msh_ctx)
		exit(STACK_OVERFLOW);
	msh_ctx->line = NULL;
	msh_ctx->env_lst = NULL;
	envs_saver(env, &msh_ctx->env_lst);
	msh_ctx->status = 0;
	msh_ctx->s_status = NULL;
	msh_ctx->heredoc_stop_f = NULL;
	return (msh_ctx);
}

void	free_before_exit(t_msh *msh_ctx, char *prompt)
{
	free_env_lst(&msh_ctx->env_lst);
	if (msh_ctx->heredoc_stop_f)
		free(msh_ctx->heredoc_stop_f);
	free(prompt);
	free(msh_ctx);
}

// lexer.c parser_handlers.c redirect.c  token_saver.c tokens_to_cmd_nodes.c executor.c node.c

int	main(int argc, char **argv, char **env)
{
	t_msh	*msh_ctx;
	char	*prompt;

	if (argc != 1 || *(argv + 1))
		exit(INPUT_ERROR);
	msh_ctx = msh_ctx_init(env);
	// print_env_list(msh_ctx->env_lst); //
	prompt = get_prompt();
	while (1)
	{
		msh_ctx->line = readline(prompt); // printf("[main] line: %s, len=%d\n", msh_ctx->line, (int)ft_strlen(msh_ctx->line));
		if (!msh_ctx->line)
		{
			msh_ctx->status = 0;
			break ;
		}
		if (msh_ctx->line && ft_strlen(msh_ctx->line))
			add_history(msh_ctx->line);
		msh_ctx->node = parser(msh_ctx);
		if (msh_ctx->node == NULL || msh_ctx->not_valid_input == 1)
			continue;
		printf("\n[main] "); print_nodes_list(msh_ctx->node);
		executor(msh_ctx);
		free_nodes_lst(&msh_ctx->node_tmp);
		free_string_array(msh_ctx->envs);
	}
	free_before_exit(msh_ctx, prompt);
	exit(0);
}
