/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_realloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 07:45:13 by heboni            #+#    #+#             */
/*   Updated: 2022/10/12 01:11:22 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*save_tmp_int_array(int **array, int *array_n)
{
	int	*tmp_array;
	int	i;

	i = -1;
	tmp_array = (int *)malloc(sizeof(int) * *array_n);
	if (tmp_array == NULL)
		exit(STACK_OVERFLOW);
	while (++i < *array_n)
		tmp_array[i] = (*array)[i];
	free(*array);
	return (tmp_array);
}

int	*int_array_realloc(int **array, int *array_n)
{
	int	*tmp_array;
	int	i;

	i = -1;
	tmp_array = NULL;
	if (*array_n != 0)
		tmp_array = save_tmp_int_array(array, array_n);
	*array_n += 1;
	*array = (int *)malloc(sizeof(int) * *array_n);
	if (*array == NULL)
		exit(STACK_OVERFLOW);
	if (tmp_array != NULL)
	{
		while (++i < (*array_n - 1))
			(*array)[i] = tmp_array[i];
		free(tmp_array);
	}
	return (*array);
}

char	**save_tmp_char_array(char **tokens, int toks_count)
{
	char	**tmp_tokens;
	int		i;

	i = -1;
	tmp_tokens = (char **)malloc(sizeof(char *) * toks_count);
	if (tmp_tokens == NULL)
		exit(STACK_OVERFLOW);
	tmp_tokens[toks_count - 1] = NULL;
	while (++i < toks_count - 1)
	{
		tmp_tokens[i] = ft_strdup(tokens[i]);
		free(tokens[i]);
	}
	free(tokens);
	return (tmp_tokens);
}

char	**tokens_realloc(char **tokens, int toks_count)
{
	char	**tmp_tokens;
	int		i;

	i = -1;
	tmp_tokens = NULL;
	if (tokens != NULL)
		tmp_tokens = save_tmp_char_array(tokens, toks_count);
	tokens = (char **)malloc(sizeof(char *) * toks_count + 1);
	if (tokens == NULL)
		exit(STACK_OVERFLOW);
	tokens[toks_count] = NULL;
	if (tmp_tokens != NULL)
	{
		while (++i < toks_count - 1)
		{
			tokens[i] = ft_strdup(tmp_tokens[i]);
			free(tmp_tokens[i]);
		}
		free(tmp_tokens);
	}
	return (tokens);
}
