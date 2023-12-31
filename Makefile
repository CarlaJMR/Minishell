NAME = minishell

SRC = minishell.c syntax.c syntax_utils.c parse.c redirection.c quote_utils.c comand_list_utils.c

LIBFT_DIR = ./libft

LIBFT = ./libft/libft.a

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

all: $(NAME) lib

$(NAME): $(OBJ) lib
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

lib:
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re lib

