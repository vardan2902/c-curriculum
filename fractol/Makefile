NAME		=	fractol
CC			=	cc
LIBFT_DIR	=	./libft
INCLUDES	=	-I$(LIBFT_DIR) -I./inc -Imlx
LINKERS		=	-L$(LIBFT_DIR) -lft -lmlx -lm -framework OpenGL -framework AppKit
CFLAGS		=	-Wall -Wextra -Werror
OBJ_DIR		=	obj
SRCS		=	main.c				formulas.c	complex_utils.c	utils.c					\
				parse_utils.c		ft_atof.c	events.c		keyboard_event_utils.c	\
				complex_utils2.c	formulas2.c
OBJS		=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
LIBFT		=	libft.a

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINKERS) $(OBJS) -o $@

$(OBJ_DIR):
	mkdir -p $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

bonus:
	@echo "No bonus files defined."

.PHONY: all clean fclean re bonus
