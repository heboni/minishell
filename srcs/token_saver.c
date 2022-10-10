/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_saver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 07:39:35 by heboni            #+#    #+#             */
/*   Updated: 2022/10/11 00:07:17 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_status_from_saver(char **tokens, int token_n, int i, t_msh *msh_ctx)
{
	//стоим на ? и не переходим на "/след символ, переход в цикле double_quotes_lexer
	tokens[token_n] = ft_strcpy_end(tokens[token_n], msh_ctx->s_status);
	// printf("[handle_status_from_saver] s_status = %s, tokens[token_n]: %s\n", msh_ctx->s_status, tokens[token_n]);
	return (i);
}

void	double_quotes_token_saver(char **tokens, int token_n, char *line, int i, t_msh *msh_ctx)
{
	int	k;

	k = ft_strlen(tokens[token_n]) - 1;
	// printf("\n[double_quotes_token_saver] i=%d, k=%d\n", i, k);
	while (line[++i] != '\"' && line[i] != '\0')
	{
		if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\"' && line[i + 1] != '?')
		{
			i = get_env_var_value_to_saver(tokens, token_n, line, i + 1, msh_ctx);
			// printf("\n[double_quotes_token_saver] tokens[token_n]=%s\n", tokens[token_n]);
			k = ft_strlen(tokens[token_n]) - 1; ////10.09 echo "''' $USER   ''"
			// i++; //19.09 "$USER" переходим на ", в while переходим на '\0' //для каких кейсов этот переход нужен
			// printf("[double_quotes_token_saver] i=%d, line[i]=%c, line[i+1]=%c\n", i, line[i], line[i+1]);
			// i = get_env_var_value(line, i + 1, envs);
			// break; //10.09 echo "''' $USER   ''"
		}
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			i = handle_status_from_saver(tokens, token_n, i + 1, msh_ctx);
			k = ft_strlen(tokens[token_n]) - 1;
			// printf("line[%d]: %c, tokens[token_n]: %s, k=%d", i, line[i], tokens[token_n], k);
		}
		else
		{
			tokens[token_n][++k] = line[i];
			// printf("%c", tokens[token_n][k]);
		}
	}
	// k = ft_strlen(tokens[token_n]) - 1; //10.09 echo "''' $USER   ''"
	tokens[token_n][++k] = '\0';
	// printf("[double_quotes_token_saver] tokens[token_n]=%s\n", tokens[token_n]);
	// printf("[double_quotes_token_saver] i=%d, line[i]=%c, line[i+1]=%c\n", i, line[i], line[i+1]);
	if (line[i] == '\0')
	{
		// printf("\n[double_quotes_token_saver] END OF LINE\n");
		return ;
	}
	if (line[i + 1] == '\'')
	{
		single_quote_token_saver(tokens, token_n, line, i + 1, msh_ctx);
		return ;
	}
	if (line[i + 1] == '\"')
	{
		double_quotes_token_saver(tokens, token_n, line, i + 1, msh_ctx);
		return ;
	}
	if (line[i + 1] == '|')
	{
		// printf("\n[double_quotes_token_saver] PIPE\n");
		return ;
	}
	if (line[i + 1] != ' ' && line[i + 1] != '\0') //добавить другие пробелы
	{
		regular_char_token_saver(tokens, token_n, line, i + 1, msh_ctx);
		return ;
	}
	// printf("\n[double_quotes_token_saver] END\n");
}

void	single_quote_token_saver(char **tokens, int token_n, char *line, int i, t_msh *msh_ctx)
{
	int	k;

	k = ft_strlen(tokens[token_n]) - 1;
	// printf("\n[single_quote_token_saver] k=%d\n", k);
	while (line[++i] != '\'')
	{
		tokens[token_n][++k] = line[i];
		// printf("%c", tokens[token_n][k]);
	}
	tokens[token_n][++k] = '\0';
	if (line[i + 1] == '\'')
	{
		single_quote_token_saver(tokens, token_n, line, i + 1, msh_ctx);
		return ;
	}
	if (line[i + 1] == '\"')
	{
		double_quotes_token_saver(tokens, token_n, line, i + 1, msh_ctx);
		return ;
	}
	if (line[i + 1] == '|')
	{
		// printf("\n[single_quote_token_saver] PIPE\n");
		return ;
	}
	if (line[i + 1] != ' ' && line[i + 1] != '\0') //добавить другие пробелы
	{
		regular_char_token_saver(tokens, token_n, line, i + 1, msh_ctx);
		return ;
	}
	// printf("\n[single_quote_token_saver] END\n");
}

void	regular_char_token_saver(char **tokens, int token_n, char *line, int i, t_msh *msh_ctx)
{
	int	k;

	while (1)
	{
		k = ft_strlen(tokens[token_n]) - 1;
		// printf("\n[regular_char_token_saver] k=%d\n", k);
		if (line[i] == '\'')
		{
			single_quote_token_saver(tokens, token_n, line, i, msh_ctx);
			return ;
		}
		if (line[i] == '\"')
		{
			double_quotes_token_saver(tokens, token_n, line, i, msh_ctx);
			return ;
		}
		if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\0' && line[i + 1] != '?')//04.08 fix $TERM $ HOME //11.08 fix $
		{
			i = get_env_var_value_to_saver(tokens, token_n, line, i + 1, msh_ctx);
			// i = get_env_var_value(line, i + 1, 0, envs);
			i++; //TO DO  внести в get_env_var_value_to_saver //нельзя, тк используется в double_saver
			continue; //04.08 fix $TERM$HOME - должен быть 1 аргумент
		}
		if (line[i] == '$' && line[i + 1] == '?')
		{
			// printf("regular\n");
			i = handle_status_from_saver(tokens, token_n, i + 1, msh_ctx);
			i++;
			// printf("line[%d]: %c, tokens[token_n]: %s\n", i, line[i], tokens[token_n]);
			continue;
		}
		if (line[i] == ' ') //добавить другие пробелы
			break ;
		if (line[i] == '\0')
			break ;
		tokens[token_n][++k] = line[i];
		// printf("k=%d: %c", k, tokens[token_n][k]);
		if (line[i] == '|' || line[i + 1] == '|' || line[i] == '>' || line[i + 1] == '>' || line[i] == '<' || line[i + 1] == '<')
			break;
		i++;
	}
	tokens[token_n][++k] = '\0';
	// printf("\n[regular_char_token_saver END]\n");
}

void	special_chars_token_saver(char **tokens, int token_n, char *line, int i)
{
	int	k;

	k = -1;
	// printf("\n[special_chars_token_saver]\n");
	tokens[token_n][++k] = line[i];
	i++;
	if ((line[i - 1] == '>' && line[i] == '>') || (line[i - 1] == '<' && line[i] == '<'))
	{
		tokens[token_n][++k] = line[i];
		i++;
	}
	tokens[token_n][++k] = '\0';
	// printf("\n[special_chars_token_saver END]\n");
}