NAME		=	libft.a
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
SRC			=	ft_atoi.c			ft_memset.c			ft_strlcpy.c		ft_bzero.c			\
				ft_putchar_fd.c		ft_strlen.c			ft_calloc.c			ft_putendl_fd.c 	\
				ft_strmapi.c		ft_isalnum.c		ft_putnbr_fd.c		ft_strncmp.c		\
				ft_isalpha.c		ft_strlcat.c		ft_putstr_fd.c		ft_strnstr.c		\
				ft_isascii.c		ft_split.c			ft_strrchr.c		ft_isdigit.c		\
				ft_strchr.c			ft_strtrim.c		ft_isprint.c		ft_memchr.c			\
				ft_strdup.c			ft_substr.c			ft_itoa.c			ft_memcmp.c			\
				ft_striteri.c		ft_tolower.c		ft_memcpy.c			ft_strjoin.c		\
				ft_toupper.c		ft_memmove.c		ft_lst_add_front.c	ft_lstdelone.c		\
				ft_lstmap.c			ft_lstadd_back.c	ft_lstiter.c		ft_lstnew.c			\
				ft_lstclear.c		ft_lstlast.c		ft_lstsize.c		ft_printf.c			\
				parse_utils.c		print_char.c		print_decimal.c		print_hex.c			\
			 	print_utils.c  		padding_utils.c		print_udecimal.c	ft_strcmp.c
OBJ			=	$(SRC:.c=.o)
BONUS_OBJ	=	$(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
