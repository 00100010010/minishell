.SILENT:
SRC_LIST = ft_free_array \
	ft_memset \
	ft_isascii \
	ft_isdigit \
	ft_itoa \
	ft_putchar_fd \
	ft_isalpha \
	ft_strlen \
	ft_array_len \
	ft_array_replace_str_chr \
	ft_array_addstr \
	ft_array_delstr \
	ft_array_strncmp \
	ft_atoi \
	ft_bzero \
	ft_malloc_error_exit \
	ft_memcpy \
	ft_memccpy \
	ft_memmove \
	ft_memchr \
	ft_memcmp \
	ft_isalnum \
	ft_isprint \
	ft_toupper \
	ft_tolower \
	ft_strchr \
	ft_strrchr \
	ft_strcmp \
	ft_strncmp \
	ft_strlcpy \
	ft_strlcat \
	ft_strnstr \
	ft_calloc \
	ft_strdup \
	ft_array_dup \
	ft_substr \
	ft_strjoin \
	ft_strjoin_char \
	ft_strtrim \
	ft_strtrim_pos \
	ft_split \
	ft_split_custom \
	ft_strmapi \
	ft_putstr \
	ft_putstr_fd \
	ft_put_array \
	ft_put_array_fd \
	ft_putendl_fd \
	ft_putnbr_fd \
	ft_int_size \
	ft_isspace \
	ft_put_color

OS			=	$(shell uname)
ifeq ($(OS), Linux)
	SRC_LIST	+= get_next_line_linux
else
	SRC_LIST	+= get_next_line_osx
endif
CFLAGS		=	-Wall -Wextra -Werror -I includes/
NAME		=	libft.a
HEADER		=	includes/libft.h
CC			=	clang
SRCS		=	$(addsuffix .c, $(SRC_LIST))
OBJ			=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@


clean:
	@rm -f $(OBJ)
	@echo "::::::::::::::::::::::::::::::::::::::::"
	@echo "\033[0;35m    libft\033[0m        binaries \033[0m    \033[0;32m |deleted|\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;35m    libft\033[0m         libft.a \033[0m    \033[0;32m |deleted|\033[0m"


re: fclean
	@echo "::::::::::::::::::::::::::::::::::::::::"
	@make


.PHONY : all clean fclean re
