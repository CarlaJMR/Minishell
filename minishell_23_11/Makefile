##########################################################
#					Instructions						 #
##########################################################

NAME =  minishell
CFLAGS = -Wall -Werror -Wextra  -g -fsanitize=address 
CC = cc 

##########################################################
#					SOURCES AND OBJS					 #
##########################################################

SRCS =  src/minishell.c src/env.c src/syntax.c src/syntax_utils.c \
		src/parse.c src/redirection.c src/quote_utils.c \
		src/comand_list_utils.c src/expander.c src/expander_utils.c
		
INCLUDES = includes

OBJS :=$(SRCS:.c=.o)

##########################################################
#					CODIGOS ANSI						 #
##########################################################


CLR_RMV		= \033[0m
RED		    = \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
CLEARBLUE	= \033[1;94m
CYAN 		= \033[1;36m
PURPLE		= \033[1;35m
WHITE 		= \033[1;37m
BLACK 		= \033[1;30m
GREY 		= \033[0;37m

##########################################################

all: $(NAME)

$(NAME) : $(OBJS)
	@make -C ./libft/ --silent --no-print-directory
	$(CC) $(CFLAGS) $(^) libft/libft.a -lreadline -o $(@)
	#@clear
	@echo "$(GREEN)Compilation of ${CLR_RMV}${CYAN}$(NAME): ${CLR_RMV}$(GREEN)⭐️"
	@echo "$(CYAN)$(NAME) ${CLR_RMV}$(GREEN)created with sucess ${CLR_RMV} ✔️"

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $(^) -o $(@)

clean:
	rm -f $(OBJS)
	make clean -C ./libft/
	#clear
	@echo "$(RED)Deleting🗑 $(PURPLE)-> $(YELLOW)$(NAME) $(CLR_RMV)$(RED)[objs]$(GREEN) ✔️${CLR_RMV}"

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft/
	#clear
	@echo "$(RED)Deleting🗑 $(PURPLE)-> $(YELLOW)$(NAME) $(CLR_RMV)$(RED)[objs] $(GREEN)✔️${CLR_RMV}"

re: fclean all

.PHONY: all clean fclean re
