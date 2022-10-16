/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 23:18:25 by heboni            #+#    #+#             */
/*   Updated: 2022/10/16 12:54:29 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_not_valid(char *argv)
{
	int	len;
	int	i;

	i = -1;
	len = ft_strlen(argv);
	while (++i < len)
	{
		if (!(ft_isalpha(argv[i]) || argv[i] == '_' || \
							(ft_isdigit(argv[i]) && i != 0)))
			return (i + 1);
	}
	return (0);
}

int	unset_builtin(t_msh *msh_ctx)
{
	char	**argv;
	int		n;

	if (!msh_ctx->env_lst || !msh_ctx->node->argv)
		return (-1);
	argv = msh_ctx->node->argv + 1;
	while (*argv != NULL)
	{
		if (is_not_valid(*argv))
		{
			printf("bash: unset: '%s': not a valid identifier\n", *argv);
			return (1);
		}
		else
		{
			n = get_env_n_if_exists(msh_ctx->env_lst, *argv);
			if (n != 0)
				env_lst_remove_n_node(&(msh_ctx->env_lst), n);
		}
		argv++;
	}
	return (0);
}
