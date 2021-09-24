PATH_SRC = ./src/
PATH_LIBFT = ./42libft/
PATH_OBJS = ./objs/
PATH_BUILTINS = $(PATH_SRC)builtins/

LIBFT = $(PATH_LIBFT)libft.a

NAME = minishell

CC = clang
CFLAGS = -Wextra -Werror -Wall -I ./includes/
RM = rm -rf

#Adicione os novos arquivos nessa linha.
#para melhor visão colocar no maximo 3 arquivos por linha
#Se necessário pode criar novas pastas dentro do src
SRC =	$(PATH_SRC)main.c \
		$(PATH_BUILTINS)pwd.c

#Os objetos
OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(PATH_LIBFT)
	$(CC) $(CFLAGS) -lreadline $(OBJS) $(LIBFT) -o $(NAME)

$(PATH_OBJS)%.o:	$(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)builtins
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
	norminette $(PATH_SRC)

git:
	git add .
	git commit -m "ajustando o nome de algumas funções no man2.md"
	git push
