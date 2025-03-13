NAME			=	minishell
CC				=	cc
MAKE			=	make
LIBFT_DIR		=	./libft
READLINE_DIR	=	./readline
INCLUDES		=	-I$(LIBFT_DIR) -I$(READLINE_DIR) -I./inc
LINKERS			=	-L$(LIBFT_DIR) -lft -L$(READLINE_DIR) -lreadline -ltermcap
CFLAGS			=	-Wall -Wextra -Werror -fsanitize=address -g
OBJ_DIR			=	obj
SRC_DIR			=	src
SRC_FILES		=	main.c ast/ast.c ast/exec.c env/ht.c env/ht_resize.c env/ht_utils.c tokenizer/tokenizer.c \
					utils/print.c builtins/echo.c builtins/pwd.c builtins/cd.c builtins/unset.c env/ht_hash_utils.c \
					builtins/exit.c builtins/env.c builtins/export.c utils/signals.c utils/validations.c \
					tokenizer/tokenization_utils.c ast/ast_utils.c ast/ast_redir.c ast/ast_cmd.c \
					ast/exec_builtins.c ast/exec_redir.c utils/std_fd_ctrl.c ast/expand_var_name.c \
					ast/char_arr_utils.c ast/expand_wildcards.c ast/exec_pipe.c ast/str_utils.c  \
					ast/cmd_utils.c ast/cmd_path_utils.c ast/expand_text.c
SRCS			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS			=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
LIBFT			=	$(LIBFT_DIR)/libft.a
MKDIR			=	mkdir -p

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINKERS) $(OBJS) -o $@

$(OBJ_DIR):
	$(MKDIR) $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR) $(dir $@)
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
