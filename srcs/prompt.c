/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:53:53 by sotherys          #+#    #+#             */
/*   Updated: 2022/10/06 22:18:13 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_filled_prompt(char *cwd, int cwd_start, int n)
{
	char	*prompt;
	char	*username;

	username = getenv("USER");
	prompt = (char *) malloc((n + 1) * sizeof(char));
	if (!prompt)
		exit(STACK_OVERFLOW);
	n = 0;
	ft_strcpy(prompt + n, SH_FG_GREEN);
	n += ft_strlen(SH_FG_GREEN);
	ft_strcpy(prompt + n, username);
	n += ft_strlen(username);
	ft_strcpy(prompt + n, SH_FG_RESET);
	n += ft_strlen(SH_FG_RESET);
	ft_strcpy(prompt + n, ":");
	++n;
	ft_strcpy(prompt + n, SH_FG_CYAN);
	n += ft_strlen(SH_FG_CYAN);
	ft_strcpy(prompt + n, cwd + cwd_start);
	n += ft_strlen(cwd + cwd_start);
	ft_strcpy(prompt + n, SH_FG_RESET);
	n += ft_strlen(SH_FG_RESET);
	ft_strcpy(prompt + n, "$ ");
	return (prompt);
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*home;
	char	cwd[1000];
	int		cwd_start;
	int		n;

	home = getenv("PWD");
	getcwd(cwd, 999);
	cwd_start = 0;
	if (ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		cwd_start = ft_strlen(home) - 1;
		cwd[cwd_start] = '~';
	}
	n = ft_strlen(SH_FG_GREEN) + ft_strlen(getenv("USER")) + \
		ft_strlen(SH_FG_RESET) + 1;
	n += ft_strlen(SH_FG_CYAN) + ft_strlen(cwd) + ft_strlen(SH_FG_RESET) + 2;
	prompt = get_filled_prompt(cwd, cwd_start, n);
	return (prompt);
}
