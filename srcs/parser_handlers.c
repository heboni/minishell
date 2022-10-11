/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:54:38 by heboni            #+#    #+#             */
/*   Updated: 2022/10/12 00:33:21 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_quotes_token_handler(int i, t_msh *msh_ctx, int *toks_count)
{
	int	tmp_i;
	
	tmp_i = i; //"
	i = double_quotes_lexer(msh_ctx->line, i, msh_ctx);
	int token_len = i - tmp_i + msh_ctx->cur_env_vars_len;
	// printf("\ni: %d, tmp_i: %d, msh_ctx->cur_env_vars_len: %d, token_len: %d", i, tmp_i, msh_ctx->cur_env_vars_len, token_len);
	(*toks_count)++;
	// printf("\n[get_tokens] toks_count: %d\n\n", toks_count);
	
	if (is_exeption_token(msh_ctx->line, tmp_i, '\"'))
	{
		// printf("\n[get_tokens] ONLY SPECIAL CHAR TOKEN\n");
		msh_ctx->exeption_indxs = int_array_realloc(&(msh_ctx->exeption_indxs), &(msh_ctx->exeption_indxs_n));
		(msh_ctx->exeption_indxs)[msh_ctx->exeption_indxs_n - 1] = (*toks_count) - 1;
	}
	
	msh_ctx->tokens = tokens_realloc(msh_ctx->tokens, *toks_count);
	msh_ctx->tokens[(*toks_count) - 1] = (char *)malloc(sizeof(char) * token_len); //выделить память под текущий токен
	msh_ctx->tokens[(*toks_count) - 1][0] = '\0';
	if (msh_ctx->tokens[(*toks_count) - 1] == NULL)
		exit(STACK_OVERFLOW);
	double_quotes_token_saver(msh_ctx->tokens, (*toks_count) - 1, tmp_i, msh_ctx);//заполнить текущий токен
	// printf("saved_token: %s\n\n", tokens[toks_count - 1]);
	// print_string_array(tokens, toks_count);
	return (i);
}

int	single_quote_token_handler(int i, t_msh *msh_ctx, int *toks_count)
{
	int	tmp_i;
	
	tmp_i = i; //'
	i = single_quote_lexer(msh_ctx->line, i, msh_ctx); //в случае '..''..' выделяю больше памяти чем нужно, обрезаю \0 в saver
	int token_len = i - tmp_i; 
	// printf("\ni: %d, tmp_i: %d, token_len: %d", i, tmp_i, token_len);//получить длину токена 
	(*toks_count)++;
	// printf("\n[get_tokens] toks_count: %d\n", toks_count);
	
	if (is_exeption_token(msh_ctx->line, tmp_i, '\''))
	{
		// printf("\n[get_tokens] ONLY SPECIAL CHAR TOKEN\n");
		msh_ctx->exeption_indxs = int_array_realloc(&(msh_ctx->exeption_indxs), &(msh_ctx->exeption_indxs_n));
		(msh_ctx->exeption_indxs)[msh_ctx->exeption_indxs_n - 1] = *toks_count - 1;
	}
	
	msh_ctx->tokens = tokens_realloc(msh_ctx->tokens, *toks_count);
	msh_ctx->tokens[*toks_count - 1] = (char *)malloc(sizeof(char) * token_len); //выделить память под текущий(новый) токен
	msh_ctx->tokens[*toks_count - 1][0] = '\0';
	if (msh_ctx->tokens[*toks_count - 1] == NULL)
		exit(STACK_OVERFLOW);
	single_quote_token_saver(msh_ctx->tokens, *toks_count - 1, tmp_i, msh_ctx);//заполнить текущий токен
	// printf("saved_token: %s\n\n", tokens[toks_count - 1]);
	// print_string_array(tokens, toks_count);
	return (i);
}

int	special_chars_token_handler(int i, t_msh *msh_ctx, int *toks_count)
{
	int	tmp_i;
	
	tmp_i = i;
	i = special_chars_lexer(msh_ctx->line, i);
	int token_len = i - tmp_i;
	(*toks_count)++;	
	i--; //если ls|grep делаем токен [|]: special_chars_lexer возвр. i~], token_len=1, возвр. на | 
	msh_ctx->tokens = tokens_realloc(msh_ctx->tokens, *toks_count);//можно делать реаллок массива токенов
	// printf("[get_tokens] %s\n", tokens[0]);
	msh_ctx->tokens[*toks_count - 1] = (char *)malloc(sizeof(char) * token_len); //выделить память под текущий(новый) токен
	msh_ctx->tokens[*toks_count - 1][0] = '\0';
	if (msh_ctx->tokens[*toks_count - 1] == NULL)
		exit(STACK_OVERFLOW);
	special_chars_token_saver(msh_ctx->tokens, *toks_count - 1, msh_ctx->line, tmp_i);
	// printf("saved_token: %s\n\n", tokens[toks_count - 1]);
	// print_string_array(tokens, toks_count);
	return (i);
}

int	regular_chars_token_handler(int i, t_msh *msh_ctx, int *toks_count)
{
	int	tmp_i;
	
	tmp_i = i;
	i = regular_char_lexer(msh_ctx->line, i, msh_ctx);
	int token_len = i - tmp_i + msh_ctx->cur_env_vars_len;
	// printf("\ni: %d, tmp_i: %d, msh_ctx->cur_env_vars_len: %d, token_len: %d", i, tmp_i, msh_ctx->cur_env_vars_len, token_len);//получить длину токена 
	(*toks_count)++;
	printf("\n[get_tokens] line[%d]: %c, toks_count: %d\n", i, msh_ctx->line[i], *toks_count);

	msh_ctx->tokens = tokens_realloc(msh_ctx->tokens, *toks_count);//можно делать реаллок массива токенов
	printf("[get_tokens] %s\n", (msh_ctx->tokens)[0]);
	msh_ctx->tokens[*toks_count - 1] = (char *)malloc(sizeof(char) * token_len); //выделить память под текущий(новый) токен
	msh_ctx->tokens[*toks_count - 1][0] = '\0';
	if (msh_ctx->tokens[*toks_count - 1] == NULL)
		exit(STACK_OVERFLOW);
	regular_char_token_saver(msh_ctx->tokens, *toks_count - 1, tmp_i, msh_ctx);//заполнить текущий токен
	// printf("saved_token: %s\n\n", tokens[toks_count - 1]);
	print_string_array(msh_ctx->tokens, *toks_count);
	return (i);
}

int	is_exeption_token(char *line, int tmp_i, char c)
{
	if (((line[tmp_i + 1] == '|' || line[tmp_i + 1] == '>' || line[tmp_i + 1] == '<')\
		&& line[tmp_i + 2] == c && (line[tmp_i + 3] == ' ' ||  line[tmp_i + 3] == '\0')) || \
		(((line[tmp_i + 1] == '>' && line[tmp_i + 2] == '>') || (line[tmp_i + 1] == '<' && line[tmp_i + 2] == '<')) && \
		line[tmp_i + 3] == c && (line[tmp_i + 4] == ' ' ||  line[tmp_i + 4] == '\0')) )
			return (1); //TO DO добавить другие пробелы
	return (0);
}
//exeption_token
//"|" '|' "<" '<' "<<" '<<' ">" '>' ">>" '>>'