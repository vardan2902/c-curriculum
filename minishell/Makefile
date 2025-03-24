NAME			=	minishell
CC				=	cc
MAKE			=	make

LIBFT_DIR		=	./libft
READLINE_DIR	=	./readline
INCLUDES		=	-I$(LIBFT_DIR) -I$(READLINE_DIR) -I./inc
LINKERS			=	-L$(LIBFT_DIR) -lft -L$(READLINE_DIR) -lreadline -ltermcap
CFLAGS			=	-Wall -Wextra -Werror

OBJ_DIR			=	obj
SRC_DIR			=	src
EXPANSION_DIR	=	expansion
UTIL_DIR		=	utils
BUILTIN_DIR		=	builtins
TOKEN_DIR		=	tokenizer
ENV_DIR			=	env
AST_DIR			=	ast

AST_SRCS		=	ast.c					exec.c				ast_utils.c			\
					ast_redir.c				ast_cmd.c			exec_builtins.c		\
					exec_redir.c			exec_pipe.c			ast_sub.c			\
					exec_handlers.c			exec_cmd.c			exec_non_builtin.c
EXPANSION_SRCS	=	expand_var_name.c		expand_wildcards.c	expand_text.c		\
					wildcard_utils.c
UTIL_SRCS		=	print.c					signals.c			validations.c		\
					std_fd_ctrl.c			helpers.c			dynamic_str.c		\
					char_arr.c				cmd_path.c			cmd.c				\
					handle_redir.c			ast_clear.c			expansion.c			\
					heredoc.c				redir.c				remove_quotes.c		\
					exec.c
BUILTIN_SRCS	=	exit.c					env.c				export.c			\
					echo.c					pwd.c				cd.c				\
					unset.c
TOKEN_SRCS		=	tokenization_utils.c	tokenizer.c
ENV_SRCS		=	ht.c					ht_resize.c			ht_utils.c			\
					ht_hash_utils.c			ht_clear.c

SRC_FILES		=	$(addprefix $(EXPANSION_DIR)/, $(EXPANSION_SRCS))				\
					$(addprefix $(UTIL_DIR)/, $(UTIL_SRCS))							\
					$(addprefix $(BUILTIN_DIR)/, $(BUILTIN_SRCS))					\
					$(addprefix $(TOKEN_DIR)/, $(TOKEN_SRCS))						\
					$(addprefix $(ENV_DIR)/, $(ENV_SRCS))							\
					$(addprefix $(AST_DIR)/, $(AST_SRCS))							\
					main.c
SRCS			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS			=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
LIBFT			=	$(LIBFT_DIR)/libft.a
MKDIR			=	mkdir -p

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LINKERS) -o $@

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
