/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:35:10 by sotherys          #+#    #+#             */
/*   Updated: 2022/10/16 15:09:44 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_msh	*msh_ctx_init(int argc, char **argv, char **env)
{
	t_msh	*msh_ctx;

	if (argc != 1 || *(argv + 1))
	{
		printf("No argvs, please. See u soon!\n");
		exit(INPUT_ERROR);
	}
	msh_ctx = NULL;
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

//rl_clear_history();
void	free_before_exit(t_msh *msh_ctx)
{
	free_env_lst(&msh_ctx->env_lst);
	if (msh_ctx->heredoc_stop_f)
		free(msh_ctx->heredoc_stop_f);
	if (msh_ctx->prompt)
		free(msh_ctx->prompt);
	free(msh_ctx);
}

// executor.c parser_handlers.c node.c+
// python3 -m norminette -R CheckForbiddenSourceHeader srcs/
int	main(int argc, char **argv, char **env)
{
	t_msh	*msh_ctx;

	rl_catch_signals = 0;
	// rl_event_hook=event;
	msh_ctx = msh_ctx_init(argc, argv, env);
	while (1)
	{
		signal(SIGINT, sigint_handler); //Ctrl-C
		signal(SIGQUIT, SIG_IGN); //Ctrl-\ ignore
		msh_ctx->prompt = get_prompt();
		msh_ctx->line = readline(msh_ctx->prompt);
		if (!msh_ctx->line)
			break ; //Ctrl-D
		if (msh_ctx->line && ft_strlen(msh_ctx->line))
			add_history(msh_ctx->line);
		msh_ctx->node = parser(msh_ctx);
		if (msh_ctx->node == NULL || msh_ctx->not_valid_input == 1)
		{
			free(msh_ctx->prompt);
			msh_ctx->prompt = NULL;
			continue ;
		}
		printf("\n[main] "); print_nodes_list(msh_ctx->node);
		executor(msh_ctx);
		free_nodes_lst(&msh_ctx->node_tmp);
		free_string_array(msh_ctx->envs);
		free(msh_ctx->prompt);
	}
	free_before_exit(msh_ctx);
	exit(0);
}
