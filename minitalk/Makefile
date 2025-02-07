CLIENT		=	client
SERVER		=	server
NAME		=	minitalk
CC			=	cc
LIBFT_DIR	=	./libft
INCLUDES	=	-I$(LIBFT_DIR)
LINKERS		=	-L$(LIBFT_DIR) -lft
CFLAGS		=	-Wall -Wextra -Werror
OBJ_DIR		=	obj
CLIENT_SRCS	=	client.c
SERVER_SRCS	=	server.c
CLIENT_OBJS	=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(CLIENT_SRCS))
SERVER_OBJS	=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SERVER_SRCS))
LIBFT		=	libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(SERVER) $(CLIENT)

$(SERVER): $(OBJ_DIR) $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINKERS) $(SERVER_OBJS) -o $@

$(CLIENT): $(OBJ_DIR) $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINKERS) $(CLIENT_OBJS) -o $@

$(OBJ_DIR):
	mkdir -p $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(CLIENT_OBJS) $(SERVER_OBJS) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(CLIENT) $(SERVER)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

bonus: $(NAME)
	@echo "No bonus files specified"

.PHONY: all clean fclean re bonus
