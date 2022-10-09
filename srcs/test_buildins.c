#include "minishell.h"

// NO LEAKS !! :)
// leaks --atExit -- ./test_buildins
// gcc srcs/test_buildins.c srcs/env.c srcs/export.c srcs/unset.c srcs/envs_lst_utils.c srcs/envs_lst_saver.c srcs/libft/* -I includes -o test_buildins && ./test_buildins
int	main(int argc, char **argv, char **env)
{
	t_msh		*msh_ctx;
	char		*line;
	char		*prompt;

	if (argc != 1)
		exit(INPUT_ERROR);
	
	msh_ctx = (t_msh *)malloc(sizeof(t_msh));
	if (!msh_ctx)
		exit(STACK_OVERFLOW);

	msh_ctx->env_lst = NULL;
	envs_saver(env, &msh_ctx->env_lst);
	
	char *exp_argv[4] = {"A1=KIRILL", "A2=KATYA", "K=", NULL};
	char *exp_argv1[4] = {"C", "=", "D", NULL};
	char *unset_argv[3] = {"A=B", "K", NULL};
	// export_builtin(msh_ctx->env, NULL, 1);
	export_builtin(msh_ctx->env_lst, exp_argv, 1);
	export_builtin(msh_ctx->env_lst, exp_argv1, 1);
	printf("\n\n++++++++++++++++++++++++++++++\n\n");
	env_builtin(msh_ctx->env_lst, exp_argv, 1);
	unset(&msh_ctx->env_lst, unset_argv, 1);
	// print_env_list(msh_ctx->env);
	env_builtin(msh_ctx->env_lst, NULL, 1);

	// while (1) {}

	free_env_lst(&msh_ctx->env_lst);
	free(msh_ctx);
	return (0);
}