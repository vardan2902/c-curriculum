NAME			=	philo
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -fsanitize=address
SRCS			=	main.c philo.c parse.c print_utils.c error_utils.c parse_utils.c \
					time_utils.c
OBJS_DIR		=	obj
OBJS			=	$(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))
LINKER_FLAGS	=	-pthread
RM				=	rm -rf
MKDIR			=	mkdir -p

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LINKER_FLAGS) $^ -o $@

$(OBJS): | $(OBJS_DIR)

$(OBJS_DIR):
	$(MKDIR) $@

$(OBJS_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
