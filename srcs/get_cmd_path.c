/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:09:32 by heboni            #+#    #+#             */
/*   Updated: 2022/10/02 00:28:38 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(char	*сmd_name, t_env *env)
{
	char	*path;
	
	if (сmd_name[0] == '.' || сmd_name[0] == '/')
	{
		//поискать в текущей директории
	}
	else
	{
		//получить все директории из env->PATH
		//пройтись по директориям, найти файл
		//что такое stat??
	}
	return (path);
}