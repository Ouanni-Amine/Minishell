SRC = builtin/ft_cd.c  builtin/ft_echo.c  builtin/ft_env.c  builtin/ft_exit.c  builtin/ft_export.c  builtin/ft_pwd.c  builtin/ft_unset.c \
	env/create_env_node.c  env/env_add_back.c  env/env_convertor.c  env/extract_env.c  env/get_env_value.c  env/get_lenght.c  env/get_shell.c  env/set_env_value.c  env/sort_export.c \
	execution/command_founder.c  execution/handle_redir.c  execution/here_doc.c  execution/multiple_cmd_fonctions.c  execution/run_multi_cmd.c  execution/run_single_cmd.c  execution/signal_part.c  execution/signals.c \
	garbage_collector/ft_malloc.c \
	parse/debug_functions.c  parse/ft_split.c  parse/lexer.c  parse/main.c  parse/parsing.c  parse/syntax_error.c  parse/test_self.c  parse/utils1.c \
	tools/env_split.c  tools/env_strlen.c  tools/ft_atoll.c  tools/ft_itoa.c  tools/ft_putchar_fd.c  tools/ft_strchr.c  tools/ft_strjoin.c  tools/here_doc_count.c  tools/set_last_status.c \
	tools/env_strdup.c  tools/error.c  tools/ft_isalnum_unscore.c  tools/ft_memcpy.c  tools/ft_putendl_fd.c  tools/ft_strcmp.c  tools/ft_strnstr.c  tools/is_valide.c \
	tools/env_strjoin.c  tools/ft_atoi.c  tools/ft_isdigit.c  tools/ft_memset.c  tools/ft_putstr_fd.c  tools/ft_strdup.c  tools/ft_strtrim.c  tools/is_valide_num.c

OBJS = $(SRC:.c=.o)

NAME = minishell
CFLAG = -Wall -Wextra -Werror
RM = rm -rf
CC = cc

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAG) -lreadline $^ -o $@

%.o : %.c parse/minishell.h
	$(CC) $(CFLAG) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean
