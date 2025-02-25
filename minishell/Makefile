NAME			=	minishell
CC				=	cc
MAKE			=	make
LIBFT_DIR		=	./libft
READLINE_DIR	=	./readline
INCLUDES		=	-I$(LIBFT_DIR) -I$(READLINE_DIR) -I./inc
LINKERS			=	-L$(LIBFT_DIR) -lft -L$(READLINE_DIR) -lreadline -ltermcap
CFLAGS			=	-Wall -Wextra -Werror -fsanitize=address
OBJ_DIR			=	obj
SRC_DIR			=	src
SRC_FILES		=	main.c ast/ast.c ast/exec.c env/ht.c env/ht_resize.c tokenizer/tokenizer.c \
					print/utils.c
SRCS			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS			=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
LIBFT			=	$(LIBFT_DIR)/libft.a
READLINE		=	$(READLINE_DIR)/libreadline.a
READLINE_CONFIG	=	$(READLINE_DIR)/config.h
MKDIR			=	mkdir -p

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(READLINE) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINKERS) $(OBJS) -o $@

$(OBJ_DIR):
	$(MKDIR) $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(READLINE_CONFIG):
	(cd $(READLINE_DIR) && bash configure)

$(READLINE): $(READLINE_CONFIG)
	$(MAKE) -C $(READLINE_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(READLINE_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

bonus:
	@echo "No bonus files defined."

.PHONY: all clean fclean re bonus
