.SILENT:
NAME 		=	minishell
EXEC		=	main tools tools2 tools3 tools4
TOOLS		=	env_tools lst_cmd_tools lst_cmd_tools2\
				lst_token_tools lst_token_tools2 pwd_tools signals tools
PARSING		=	parser parsing_cleaner_tools parsing_cleaner\
				parsing_expander_tools parsing_expander\
				parsing_redir_tools parsing_redir parsing_tokenizer\
				parsing_tools2 parsing_tools pre_parsing
READLINE	=	main tools tools2
TERMCAPS	=	cursor hist_tools hist_tools2 hist init loop\
				readline tools
BUILTINS	=	cd echo env exit exit_tools export export_tools1 export_tools2 \
				pwd unset
MAIN		=	main
SRC			=	$(addsuffix .c, $(addprefix srcs/tools/, $(TOOLS))) \
				$(addsuffix .c, $(addprefix srcs/exec/exec_, $(EXEC))) \
				$(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
				$(addsuffix .c, $(addprefix srcs/readline/readline_, $(READLINE))) \
				$(addsuffix .c, $(addprefix srcs/termcaps/tc_, $(TERMCAPS))) \
				$(addsuffix .c, $(addprefix srcs/exec/builtins/exec_builtin_, $(BUILTINS))) \
				$(addsuffix .c, $(addprefix srcs/, $(MAIN)))
HEADER		=	includes/minishell.h
CC			=	clang
CFLAGS		= 	-Werror -Wextra -Wall -I includes/ -I libft/includes/
LIBFT		=	-L libft -lft -lncurses
LFLAGS		=	-I/libft/includes/libft.h ./libft/libft.a -lncurses
OBJ			=	$(SRC:.c=.o)


all:	$(NAME)
	@echo "🔥 minishell"
	@echo "🔥 libft"

go: all
	@./minishell

bonus: $(NAME)
	@echo "🔥 minishell bonus"
	@echo "🔥 libft"

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

%.o: %.c $(HEADER)
	@$(CC) -c $(CFLAGS) -o $@ $<

clean:
	@make clean -C libft
	@rm -rf $(OBJ)
	@echo "::::::::::::::::::::::::::::::::::::::::"
	@echo "\033[0;34mminishell\033[0m        binaries \033[0m    \033[0;32m |deleted|\033[0m"

fclean:
	@make fclean -C libft
	@rm -rf $(OBJ)
	@echo "::::::::::::::::::::::::::::::::::::::::"
	@echo "\033[0;34mminishell\033[0m        binaries \033[0m    \033[0;32m |deleted|\033[0m"
	@rm -rf $(NAME)
	@echo "\033[0;34mminishell\033[0m     minishell.a \033[0m    \033[0;32m |deleted|\033[0m"

re:	fclean
	@echo "::::::::::::::::::::::::::::::::::::::::"
	@make

norme:
	@norminette $(SRC) $(HEADER)

.PHONY : all clean fclean re bonus go norme
