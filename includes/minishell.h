/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:24:04 by sotherys          #+#    #+#             */
/*   Updated: 2022/10/16 20:03:10 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

# include "libft.h"
# include "msh_node.h"

# define STACK_OVERFLOW -1
# define INPUT_ERROR	-2

# define SH_FG_RED "\033[31m"
# define SH_FG_GREEN "\033[32m"
# define SH_FG_RESET "\033[39m"
# define SH_FG_CYAN "\033[36m"

int	g_lobal_status;

typedef struct s_env
{
	char			*var_name;
	char			*var_value;
	struct s_env	*next;
}					t_env;

typedef struct s_msh
{
	char	*prompt;
	char	*line;
	t_node	*node;
	t_node	*node_tmp;
	t_env	*env_lst;
	char	**envs;
	char	*s_status;
	char	**tokens;
	int		toks_count;
	int		*exeption_indxs;
	int		exeption_indxs_n;
	int		not_valid_input;
	int		cur_env_vars_len;
	int		p_r;
	int		p_wr;
	int		is_stdin_pipe;
	int		is_stdout_pipe;
	char	*heredoc_stop_f;
	int		heredoc_fd;
}				t_msh;

char	*get_prompt(void);

//parser
t_node	*parser(t_msh *msh_ctx);
void	free_from_parser(t_msh *msh_ctx);
char	**get_tokens(char *line, t_msh *msh_ctx);

//parser_handlers
int		double_quotes_token_handler(int i, t_msh *msh_ctx, int *toks_count);
int		single_quote_token_handler(int i, t_msh *msh_ctx, int *toks_count);
int		special_chars_token_handler(int i, t_msh *msh_ctx, int *toks_count);
int		regular_chars_token_handler(int i, t_msh *msh_ctx, int *toks_count);
int		is_exeption_token(char *line, int tmp_i, char c);

//check_input
void	check_valid_input(char **tokens, int t_count, t_msh *msh_ctx);

//array_realloc
char	**tokens_realloc(char **tokens, int toks_count);
int		*int_array_realloc(int **array, int *array_n);
int		*int_array_realloc1(int *array, int array_n);
int		**int_array_realloc0(int **array, int *array_n);

// lexer
int		single_quote_lexer(char *line, int i, t_msh *msh_ctx);
int		double_quotes_lexer(char *line, int i, t_msh *msh_ctx);
int		regular_char_lexer(char *line, int i, t_msh *msh_ctx);
int		special_chars_lexer(char *line, int i);
int		handle_status_from_lexer(int i, t_msh *msh_ctx);

// token_saver
void	single_quote_token_saver(char **tokens, int token_n, \
													int i, t_msh *msh_ctx);
void	double_quotes_token_saver(char **tokens, int token_n, \
													int i, t_msh *msh_ctx);
void	regular_char_token_saver(char **tokens, int token_n, \
													int i, t_msh *msh_ctx);
void	special_chars_token_saver(char **tokens, int token_n, \
													char *line, int i);
int		handle_status_from_saver(char **tokens, int token_n, \
													int i, t_msh *msh_ctx);

// tokens_to_ast_nodes
t_node	*tokens_to_ast_nodes(char **tokens, int toks_count, t_msh *msh_ctx);
int		is_in_exception_indexes(t_msh *msh_ctx, int token_i);

// node
void	print_nodes_list(t_node *ast_nodes);
int		is_special_token(char **tokens, int t_i, t_msh *msh_ctx);
int		is_special_symbols(char *token);
void	ast_node_lst_push_bottom(t_node **head, t_redirect_type type);
void	node_lst_push_bottom(t_node **head, char **tokens, int *t_i, \
														t_msh *msh_ctx);
t_node	*get_last_ast_node(t_node *head);
char	**get_node_argv(char **tokens, int *token_i, t_msh *msh_ctx, \
															t_node *new);
int		is_pipe_token(char **tokens, int t_i, t_msh *msh_ctx);
int		is_redirect_token(char **tokens, int t_i, t_msh *msh_ctx);

// redirect
int		redir_token_handler(char **tokens, int *t_i, t_msh *msh_ctx, \
															t_node *new);

// get_env
int		pass_env_var_value_from_lexer(char *line, int i, t_msh *msh_ctx);
int		get_env_var_value_to_saver(char **tokens, int token_n, \
													int i, t_msh *msh_ctx);
char	*get_env_value_by_name_from_envs(void *name, t_msh *msh_ctx);
void	env_val_len_by_name_from_lst(char *name, t_msh *msh_ctx);

// get_cmd_path
char	*get_cmd_path(char *cmd_name, t_msh *msh_ctx);

// executor
void	executor(t_msh *msh_ctx);
void	one_cmd_executor(t_msh *msh_ctx);
void	ft_puterror(char *s1, char *s2);

// exec
int		is_builtin(char *cmd_name);
void	proxy_to_builtins(t_msh *msh_ctx);
void	exec_builtin(t_msh *msh_ctx);

// heredoc
void	ms_write_heredoc_file(t_msh *msh_ctx);

// signals
void	sigint_handler(int sig);
void	signal_while_child_handler(int sig);

// buildins
int		cd_builtin(t_msh *msh_ctx);
int		echo_builtin(t_msh *msh_ctx);
int		exit_builtin(t_msh *msh_ctx);
int		pwd_builtin(t_msh *msh_ctx);
int		env_builtin(t_msh *msh_ctx);
int		export_builtin(t_msh *msh_ctx);
int		unset_builtin(t_msh *msh_ctx);
int		is_not_valid(char *argv);

// free_utils
void	free_nodes_lst(t_node **ast_nodes);
void	free_string_array(char **argv);

// utils
char	*alloc(int token_len);
int		get_tokens_count(char **tokens);
void	print_string_array(char **argv, int count);
void	print_int_array(int *array, int n);
int		len_2d_array(char **string);

// envs_lst_saver
void	envs_saver(char **env, t_env **envs_lst);
char	*get_env_value_to_save(char *env, int i, int k);
char	**envs_lst_to_char_array(t_env *env_lst);

// get_env
char	*get_env_name_from_line(char *line, int tmp_i, int var_len);
void	put_env_value_to_token(char *var_value, char **tokens, int token_n);

// envs_lst_utils
void	env_lst_push_bottom(t_env **head, char *name, char *value);
t_env	*get_last_node(t_env *head);
void	free_env_lst(t_env **lst);
int		get_envs_count(t_env *envs);
void	export_print_env_list(t_env *envs);
char	*get_env_name_to_buildin(char *argv, int *k);
int		get_env_n_if_exists(t_env *envs, char *name);
int		env_lst_update_node(t_env *envs, char *name, char *value);
void	env_lst_remove_n_node(t_env **envs, int n);

#endif
