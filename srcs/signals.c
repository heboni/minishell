/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:32:05 by heboni            #+#    #+#             */
/*   Updated: 2022/10/16 19:09:44 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n\"Ctrl+C\" was pressed\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_lobal_status = 1;
	}
}

//Реакция на нажатие Ctrl-"C" и Ctrl-"\" во время выполнения cmds
void	signal_while_child_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n\"Ctrl+C\" was pressed\n", 1);
		rl_done = 1;
		g_lobal_status = 130;
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", 1);
		ft_putstr_fd("\"Ctrl+\\\" was pressed\n", 1);
		g_lobal_status = 131;
	}
}
