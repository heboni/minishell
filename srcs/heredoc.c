/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:06:01 by heboni            #+#    #+#             */
/*   Updated: 2022/10/16 18:55:06 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_write_heredoc_file(t_msh *msh_ctx)
{
	char	*str;

	str = NULL;
	if (msh_ctx->node->ll_f == NULL)
		return ;
	while (1)
	{
		str = readline("> ");
		if (str == NULL)
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
