/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:35:30 by heboni            #+#    #+#             */
/*   Updated: 2022/10/14 20:20:52 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_env
{
	char			*var_name;
	char			*var_value;
	struct s_env	*next;
}					t_env;

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