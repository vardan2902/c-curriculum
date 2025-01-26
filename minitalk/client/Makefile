NAME		=	client
CC			=	cc
LIBFT_DIR	=	../libft
INCLUDES	=	-I$(LIBFT_DIR) -I./inc
LINKERS		=	-L$(LIBFT_DIR) -lft
CFLAGS		=	-Wall -Wextra -Werror
SRC_DIR		=	src
OBJ_DIR		=	obj
SRCS		=	main.c	bit_utils.c
OBJS		=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
LIBFT		=	libft.a

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINKERS) $(OBJS) -o $@

$(OBJ_DIR):
	mkdir -p $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
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
