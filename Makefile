NAME		= minishell

SRCS_DIR	= srcs/
HEAD_DIR	= includes/
BUILD_DIR	= build/

SRCS_FILES	= main.c							\
			  libft/ft_strlen.c 				\
			  libft/ft_strcpy.c					\
			  libft/ft_strcmp.c					\
			  libft/ft_strncmp.c				\
			  libft/ft_strdup.c					\
			  libft/ft_strjoin.c				\
			  libft/ft_strjoin_3.c				\
			  libft/ft_putstr_fd.c				\
			  libft/ft_isalpha.c				\
			  libft/ft_isdigit.c 				\
			  libft/ft_strchr.c 				\
			  libft/ft_atoi.c 					\
			  libft/ft_itoa.c 					\
			  builtins/cd.c 					\
			  builtins/echo.c 					\
			  builtins/env.c 					\
			  builtins/exit.c 					\
			  builtins/export.c 				\
			  builtins/pwd.c 					\
			  builtins/unset.c 					\
			  parser.c							\
			  parser_handlers.c					\
			  lexer.c							\
			  token_saver.c						\
			  check_input.c 					\
			  array_realloc.c 					\
			  envs_lst_saver.c					\
			  envs_lst_utils.c					\
			  envs_lst_utils2.c					\
			  get_env.c 						\
			  tokens_to_cmd_nodes.c 			\
			  node.c							\
			  get_cmd_path.c 					\
			  redirect.c						\
			  prompt.c							\
			  executor.c 						\
			  heredoc.c 						\
			  utils.c							\
			  utils_special.c					\
			  utils_free.c 						\

OBJS_FILES	= $(SRCS_FILES:.c=.o)

SRCS 		= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS		= $(addprefix $(BUILD_DIR), $(OBJS_FILES))
DEPS		= $(OBJS:.o=.d)

CC			= gcc
# CFLAGS		=  -MMD
CFLAGS		= -Wall -Werror -Wextra -MMD
LIBS		= -lreadline

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

$(BUILD_DIR)%.o: $(SRCS_DIR)%.c $(BUILD_DIR)%.d
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(HEAD_DIR) -o $@ -c $<

$(BUILD_DIR)%.d: ;

$(DEPS):
-include $(wildcard $(DEPS))

clean: 
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)

re:
	make fclean
	make all

.PHONY: all bonus clean fclean re