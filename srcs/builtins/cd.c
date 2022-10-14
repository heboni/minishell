/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:20:05 by heboni            #+#    #+#             */
/*   Updated: 2022/10/14 13:42:08 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//обновлять PWD и  OLDPWD
//отрисовывать новый prompt или он сам новый отрисуется в зависимости от PWD
//если аргументов > 1, cd игнорирует второй аргумент
//with only a relative or absolute path
//getcwd, chdir 
//chdir: In order for a directory to become the current directory, a process must have execute (search) access to the directory.
int	exec_chdir(t_msh *msh_ctx, char	*dir_to, char *old_dir, char *new_dir)
{
	if (chdir(dir_to) != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", dir_to);
		free(old_dir);
		return (1);
	}
	else
	{
		new_dir = getcwd(NULL, 0); printf("new_dir: %s\n", new_dir);
		if (!env_lst_update_node(msh_ctx->env_lst, "PWD", new_dir))
			env_lst_push_bottom(&(msh_ctx->env_lst), "PWD", new_dir);
		//заменить PWD на new_dir
		//заменить OLDPWD на old_dir
		if (!env_lst_update_node(msh_ctx->env_lst, "OLDPWD", old_dir))
			env_lst_push_bottom(&(msh_ctx->env_lst), "OLDPWD", old_dir);
		free(old_dir);
		free(new_dir);
	}
	return (0);
}

int	cd_builtin(t_msh *msh_ctx)
{
	char	**argv;
	char	*new_dir;
	char	*old_dir;
	char	*dir_to;
	
	argv = msh_ctx->node->argv + 1;
	old_dir = getcwd(NULL, 0);
	new_dir = NULL;
	if (*argv == NULL)
		dir_to = getenv("HOME");
	else
		dir_to = *argv;
	return (exec_chdir(msh_ctx, dir_to, old_dir, new_dir));
}

// int	cd_builtin(t_msh *msh_ctx)
// {
// 	char	**argv;
// 	char	*new_dir;
// 	char	*old_dir;
	
// 	argv = msh_ctx->node->argv + 1;
// 	old_dir = getcwd(NULL, 0);
// 	if (*argv == NULL)
// 	{
// 		if (chdir(getenv("HOME")) != 0)
// 		{
// 			printf("bash: cd: %s: No such file or directory\n", getenv("HOME"));
// 			free (old_dir);
// 			return (1);
// 		}
// 		else
// 		{
// 			new_dir = getcwd(NULL, 0); printf("new_dir: %s\n", new_dir);
// 			//заменить PWD на new_dir
// 			//заменить OLDPWD на old_dir
// 		}
// 		return (0);
// 	}
// 	if (chdir(*argv) != 0)
// 	{
// 		printf("bash: cd: %s: No such file or directory\n", *argv);
// 		free (old_dir);
// 		return (1);
// 	}
// 	else
// 	{
// 		new_dir = getcwd(NULL, 0); printf("new_dir: %s\n", new_dir);
// 		//заменить PWD на new_dir
// 		//заменить OLDPWD на old_dir
// 	}
// 	return (0);
// }

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