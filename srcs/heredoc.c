/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:06:01 by heboni            #+#    #+#             */
/*   Updated: 2022/10/15 15:54:12 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int event(void)
{
	return (0);
}

void	signal_while_heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n\"Ctrl+C\" while_heredoc was pressed\n", 1);
		// rl_on_new_line();
		// rl_replace_line("", 1);
		rl_done = 1;
		rl_redisplay();
		// g_lobal_status = 1;
	}
}

void	ms_write_heredoc_file(t_msh *msh_ctx)
{
	char	*str;

	str = NULL;
	if (msh_ctx->node->ll_f == NULL)
		return ;
	while (1)
	{
		rl_event_hook=event;
		signal(SIGINT, signal_while_heredoc_handler);
		str = readline("> ");
		if (str == NULL) //Ctrl-D
		{
			printf("!!! EOF instead of «%s»\n",
				msh_ctx->heredoc_stop_f);
			break ;
		}
		if (ft_strcmp(msh_ctx->heredoc_stop_f, str) == 0)
		{
			free(str);
			break ;
		}
		write(msh_ctx->heredoc_fd, str, ft_strlen(str));
		write(msh_ctx->heredoc_fd, "\n", 1);
		free(str);
	}
	close(msh_ctx->heredoc_fd);
	msh_ctx->heredoc_fd = open(".del", O_RDONLY);
}
