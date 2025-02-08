CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -I./libft
AR			=	ar
ARFLAGS		=	rcs
SRCS		=	ft_printf.c		parse_utils.c		print_char.c		print_decimal.c	\
				print_hex.c 	print_utils.c  		padding_utils.c		print_udecimal.c
OBJS		=	$(SRCS:.c=.o)
HEADER		=	ft_printf.h
NAME		=	libftprintf.a
LIBFT_DIR	=	libft
LIBFT		=	libft.a	

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/$@ $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

bonus:
	@echo "No bonus files defined."

.PHONY: all clean fclean re bonus
