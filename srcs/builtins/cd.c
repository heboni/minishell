/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:20:05 by heboni            #+#    #+#             */
/*   Updated: 2022/10/10 20:32:42 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//обновлять PWD и  OLDPWD
//отрисовывать новый prompt или он сам новый отрисуется в зависимости от PWD

int	cd(char **argv) //getcwd, chdir //with only a relative or absolute path 
{
	int	chdir_res;
	
	if (!argv)
		return (-1);
	printf("%s\n", *argv);
	chdir_res = chdir(*argv);
	// если аргументов > 1, cd игнорирует второй аргумент
	//ERROR: return (-1);
	char *dir = getcwd(NULL, 0);
	printf("%s\n", dir);
	return (chdir_res);
}
//chdir: In order for a directory to become the current directory, a process must have execute (search) access to the directory.

/*
int	main(void)
{
	// char *argv[2] = {"/Users/ekaterinasvincickaa/Documents/21_school/21school-main/minishell/42_minishell/srcs/libft", NULL};
	// char *argv[2] = {"libft/", NULL};
	// char *argv[2] = {"./libft", NULL};
	// char *argv[2] = {"..", NULL};
	char *argv[2] = {NULL, NULL};
	
	// cd .././includes из srcs
	printf("%d\n", cd(argv));
	
	char *dir = getcwd(NULL, 0);
	printf("\n%s\n", dir);
	return (0);
}
*/