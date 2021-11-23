PATH_SRC = ./src/
PATH_LIBFT = ./42libft/
PATH_OBJS = ./objs/
PATH_BUILTINS = $(PATH_SRC)builtins/
PATH_ERRORS = $(PATH_SRC)errors/
PATH_UTILS = $(PATH_SRC)utils/
PATH_EXEC = $(PATH_SRC)exec/
PATH_PARSER = $(PATH_SRC)parser/
PATH_INCLUDES = ./includes/

LIBFT = $(PATH_LIBFT)libft.a

NAME = minishell

CC = clang
CFLAGS = -Wextra -Werror -Wall -I ./includes/ #-fsanitize=address
RM = rm -rf

SRC =	$(PATH_SRC)main.c \
		$(PATH_BUILTINS)pwd.c $(PATH_BUILTINS)ft_echo.c $(PATH_BUILTINS)ft_cd.c \
		$(PATH_BUILTINS)ft_env.c $(PATH_BUILTINS)ft_export.c $(PATH_BUILTINS)ft_unset.c \
		$(PATH_ERRORS)errors.c $(PATH_ERRORS)more_errors.c \
		$(PATH_UTILS)utils_free.c $(PATH_UTILS)utils_lst.c $(PATH_UTILS)handle_signal.c \
		$(PATH_UTILS)utils.c $(PATH_UTILS)utils_struct.c \
		$(PATH_EXEC)exec.c $(PATH_EXEC)utils_exec.c\
		$(PATH_PARSER)parser_cmd.c $(PATH_PARSER)redirection.c $(PATH_PARSER)parser_redic.c \
		$(PATH_PARSER)parser_quotes.c $(PATH_PARSER)aux_parser.c $(PATH_PARSER)pipe.c

OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(PATH_LIBFT)
	$(CC) $(CFLAGS) -lreadline  $(OBJS) $(LIBFT) -o $(NAME)

$(PATH_OBJS)%.o:	$(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)builtins
	@mkdir -p $(PATH_OBJS)errors
	@mkdir -p $(PATH_OBJS)utils
	@mkdir -p $(PATH_OBJS)exec
	@mkdir -p $(PATH_OBJS)parser
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	$(RM) $(PATH_OBJS)
	make clean -C $(PATH_LIBFT)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(PATH_LIBFT)

re: fclean all

.PHONY: re all fclean clean

norminha:
	norminette $(PATH_SRC) $(PATH_INCLUDES) $(PATH_LIBFT)

add:	fclean
	git add .
	git commit -m "começando readme"

push:	add
	git push

teste:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./minishell

install:
	sudo apt-get install libreadline-dev