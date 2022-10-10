/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:26:06 by heboni            #+#    #+#             */
/*   Updated: 2022/10/11 00:06:48 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	regular_char_lexer(char *line, int i, t_msh *msh_ctx)
{
	// printf("in regular\n");
	while (1)
	{
		if (line[i] == '\'')
		{
			i = single_quote_lexer(line, i, msh_ctx);
			if (line[i] == '\'') //ech'o' 90
				i++;
			if (line[i] == '\"') //ec'h'"o" 90   01.08
				i++;
		}
		if (line[i] == '\"')
		{
			i = double_quotes_lexer(line, i, msh_ctx);
			if (line[i] == '\"') //ech"o" 90
				i++;
		}
		if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\0' && line[i + 1] != '?')//04.08 fix $TERM $ HOME //11.08 fix $//2.10 fix $?
		{
			i = get_env_var_value_to_lexer(line, i + 1, msh_ctx); // i = get_env_var_value_to_lexer(line, i + 1, 0, envs);
			i++;
			continue; //04.08 fix $TERM$HOME - должен быть 1 аргумент
		}
		if (line[i] == '$' && line[i + 1] == '?')
			i = handle_status_from_lexer(i + 1, msh_ctx);
		// printf("%c", line[i]);
		if (line[i] == ' ') //добавить другие пробелы
			break ;
		if (line[i] == '\0')
			break ;
		if (line[i] == '|' || line[i + 1] == '|' || line[i] == '>' || line[i + 1] == '>' || line[i] == '<' || line[i + 1] == '<')
			break; //после printf для кейсов a| b, a|b
		i++;
	}
	return (i);
}

int	special_chars_lexer(char *line, int i) //из regular_char не надо вызывать special_chars_lexer, special_chars_lexer будет 
{ // всегда вызываться на уровень выше, чтобы было корректное token_count
	// printf("%c", line[i]); //4.10
	i++;
	if ((line[i - 1] == '>' && line[i] == '>') || (line[i - 1] == '<' && line[i] == '<'))
	{
		// printf("%c\n", line[i]);
		i++;
	}
	return (i);
}

int	handle_status_from_lexer(int i, t_msh *msh_ctx)
{
	//стоим на ? и не переходим на "/след символ, переход в цикле double_quotes_lexer
	if (msh_ctx->s_status)
		free(msh_ctx->s_status);
	msh_ctx->s_status = ft_itoa(msh_ctx->status);
	// printf("[handle_status_from_lexer] s_status = %s\n", msh_ctx->s_status);
	msh_ctx->cur_env_vars_len += ft_strlen(msh_ctx->s_status);
	return (i);
}

int	double_quotes_lexer(char *line, int i, t_msh *msh_ctx)
{
	// printf("in double\n");
	while (line[++i] != '\"')
	{
		// printf("double[%d]: %c\n", i, line[i]);
		// printf("%c", line[i]); //05.08
		if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\"' && line[i + 1] != '?') //11.08 fix "$","$ aaa"//2.10 fix "$?"
			i = get_env_var_value_to_lexer(line, i + 1, msh_ctx); // i = get_env_var_value_to_lexer(line, i + 1, 0, envs); //05.08
		// else//4.10
		// 	printf("%c", line[i]); //05.08 //4.10
		if (line[i] == '$' && line[i + 1] == '?')
			i = handle_status_from_lexer(i + 1, msh_ctx);
		if (line[i] == '\0')
		{
			printf("Not closed quote \"\n");
			msh_ctx->not_valid_input = 1;
			return (i);// break;
		}
	} //TO DO в кажом if ниже возвращается i, удалить из каждого и cделать else if
	if (line[i + 1] == '\"')
	{
		i = double_quotes_lexer(line, i + 1, msh_ctx);
		return (i); //01.08
	}
	if (line[i + 1] == '\'')
	{
		i = single_quote_lexer(line, i + 1, msh_ctx);
		return (i); //01.08
	}
	if (line[i + 1] == '|')
		return (i); //03.08
	if (line[i + 1] != ' ' && line[i + 1] != '\0') //04.08 //добавить другие пробелы
	{
		i = regular_char_lexer(line, i + 1, msh_ctx);
		return (i); //01.08
	}
	return (i);
}

int	double_quotes_lexer0(char *line, int i, t_msh *msh_ctx)
{
	// printf("in double\n");
	while (line[++i] != '\"')
	{
		// printf("double[%d]: %c\n", i, line[i]);
		// printf("%c", line[i]); //05.08
		if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\"' && line[i + 1] != '?') //11.08 fix "$","$ aaa"//2.10 fix "$?"
			i = get_env_var_value_to_lexer(line, i + 1, msh_ctx); // i = get_env_var_value_to_lexer(line, i + 1, 0, envs); //05.08
		// else//4.10
		// 	printf("%c", line[i]); //05.08 //4.10
		if (line[i] == '\0')
		{
			printf("Not closed quote \"\n");
			msh_ctx->not_valid_input = 1;
			return (i);// break;
		}
	} //TO DO в кажом if ниже возвращается i, удалить из каждого
	if (line[i + 1] == '\"')
	{
		i = double_quotes_lexer(line, i + 1, msh_ctx);
		return (i); //01.08
	}
	if (line[i + 1] == '\'')
	{
		i = single_quote_lexer(line, i + 1, msh_ctx);
		return (i); //01.08
	}
	if (line[i + 1] == '|')
		return (i); //03.08
	if (line[i + 1] != ' ' && line[i + 1] != '\0') //04.08 //добавить другие пробелы
	{
		i = regular_char_lexer(line, i + 1, msh_ctx);
		return (i); //01.08
	}
	return (i);
}

int	single_quote_lexer(char *line, int i, t_msh *msh_ctx)
{
	while (line[++i] != '\'')
	{
		// printf("single: %c\n", line[i]);
		// printf("%c", line[i]); //4.10
		if (line[i] == '\0')
		{
			printf("Not closed quote \'\n");
			msh_ctx->not_valid_input = 1;
			return (i);// break;
		}
	} //TO DO в кажом if ниже возвращается i, удалить из каждого и cделать else if
	// printf("\nSINGLE_I: %d", i);
	if (line[i + 1] == '\'')
	{
		i = single_quote_lexer(line, i + 1, msh_ctx);
		return (i); //01.08
	}	
	if (line[i + 1] == '\"')
	{
		i = double_quotes_lexer(line, i + 1, msh_ctx);
		return (i); //01.08
	}
	if (line[i + 1] == '|')
		return (i); //03.08
	if (line[i + 1] != ' ' && line[i + 1] != '\0') //04.08 //добавить другие пробелы
	{
		i = regular_char_lexer(line, i + 1, msh_ctx);
		return (i); //01.08
	}
	// printf("\nSINGLE_RETURN_I: %d", i);
	return (i);
}
