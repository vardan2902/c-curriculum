NAME			=	push_swap
BONUS			=	checker
CC				=	cc
INCLUDES		=	-Ilibft
LINKERS			=	-Llibft -lft
LIBFT_DIR		=	libft
LIBFT			=	$(LIBFT_DIR)/libft.a
CFLAGS			=	-Wall -Wextra -Werror
SRCS			=	push_swap.c			pop.c				rotate.c		count_best_moves.c	\
					ps_parse.c			sort5.c				dstack.c		ps_parse_utils.c	\
					sort_utils.c		error_utils.c		push.c			stack_utils.c		\
					instruction_utils.c	swap.c				min_max.c		rev_rotate.c		\
					tab_utils.c
BONUS_SRCS		=	checker.c			dstack.c			pop.c			push.c				\
					swap.c				rotate.c			rev_rotate.c	stack_utils.c		\
					ps_parse.c			ps_parse_utils.c	tab_utils.c		error_utils.c
OBJS_DIR		=	obj
OBJS			=	$(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))
BONUS_OBJS		=	$(patsubst %.c, $(OBJS_DIR)/%.o, $(BONUS_SRCS))
MKDIR			=	mkdir -p
RM				=	rm -rf

.DEFAULT_GOAL = all

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINKERS) $(OBJS) -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJS) $(BONUS_OBJS): | $(OBJS_DIR)

$(OBJS_DIR):
	$(MKDIR) $@

bonus: $(BONUS) 

$(BONUS): $(LIBFT) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINKERS) $(BONUS_OBJS) -o $@

$(OBJS_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
