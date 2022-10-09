/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:09:32 by heboni            #+#    #+#             */
/*   Updated: 2022/10/09 16:11:08 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*allocate_cmd_path(const char *cmd, size_t s_cmd, char *path, size_t s_path)
{
	char	*new;
	size_t	i;
	int		flg;

	flg = s_path != 0;
	i = -1;
	new = malloc(sizeof(char) * (s_cmd + s_path + 1 + flg));
	if (!new)
		return (NULL);
	while (++i < s_path)
		new[i] = path[i];
	if (flg)
		new[s_path] = '/';
	i = -1;
	while (++i < s_cmd)
		new[i + s_path + flg] = cmd[i];
	new[i + s_path + flg] = 0;
	if (!access(new, X_OK))
		return (new);
	free(new);
	return (NULL);
}

char	fill_cmd_path(char **dst, const char *cmd, char *path)
{
	size_t		size_cmd;
	size_t		size_path;
	static char	*tmp;

	size_cmd = 0;
	if (!tmp)
		tmp = *dst;
	while (cmd[size_cmd])
		size_cmd++;
	*dst = allocate_cmd_path(cmd, size_cmd, path, 0);
	if (*dst)
		return (0);
	while (*path)
	{
		size_path = 0;
		while (path[size_path] && path[size_path] != ':')
			size_path++;
		*dst = allocate_cmd_path(cmd, size_cmd, path, size_path);
		if (*dst)
			return (0);
		path += size_path + (path[size_path] == ':');
	}
	*dst = tmp;
	return (1);
}

char	*get_cmd_path(char *cmd_name, t_msh *msh_ctx)
{
	char	*cmd_path;
	char	*env_path;
	char	*path;
	
	cmd_path = NULL;
	if (cmd_name == NULL && ft_strlen(cmd_name) == 0)
		return (cmd_path);
	env_path = get_env_value_by_name_from_envs("PATH", msh_ctx);
	if (!env_path || ft_strchr(cmd_name, '/'))
		path = "";
	else
		path = env_path;
	if (fill_cmd_path(&cmd_path, cmd_name, path))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (cmd_path);//exit(127);
	}
	return (cmd_path);
}