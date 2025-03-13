#include "minishell.h"

extern volatile sig_atomic_t	g_signal_int;

/*
static void print_node(t_ast *node, int level)
{
    for (int i = 0; i < level; i++)
        printf("  "); // Indent based on the level

    if (!node)
    {
        printf("(null)\n");
        return;
    }

    switch (node->token)
    {
    case T_CMD:
        printf("CMD: %s\n", node->cmd ? node->cmd->name : "(null)");
        break;
    case T_PIPE:
        printf("PIPE\n");
        break;
    case T_AND:
        printf("AND\n");
        break;
    case T_OR:
        printf("OR\n");
        break;
    case T_NONE:
        printf("NONE\n");
        break;
    default:
        printf("UNKNOWN\n");
        break;
    }

    if (node->is_subshell)
    {
        for (int i = 0; i < level + 1; i++)
            printf("  ");
        printf("(subshell)\n");
    }
}

void print_ast(t_ast *node, int level)
{
    if (!node)
        return;

    // Print the current node
    print_node(node, level);

    // Recursively print the left and right children
    print_ast(node->left, level + 1);
    print_ast(node->right, level + 1);
}
*/

void	process_prompt(char *line, t_ht *map)
{
	t_list	*token_lst;
	t_ast	*ast;
	char	*status;

	if (*line == '\0')
		return (free(line));
	add_history(line);
	token_lst = get_token_lst(line);
	free(line);
	if (!token_lst)
		return ;
	ast = ast_create_from_tokens(&token_lst, 0);
	if (!ast)
		return (ht_set(map, "?", "2"));
//	print_ast(ast, 0);
	status = ft_itoa((unsigned char)execute_ast(ast, map));
	ht_set(map, "?", status);
}

int	prompt_loop(t_ht *map)
{
	char			*line;
	unsigned char	status;

	if (!isatty(fileno(stdin)))
	{
		ht_set(map, "#ISNOTATTY", "TRUE");
		line = ft_strtrim(get_next_line(STDIN_FILENO), "\n");
		while (line)
		{
			g_signal_int = 0;
			if (!line)
				return (0);
			process_prompt(line, map);
			line = ft_strtrim(get_next_line(STDIN_FILENO), "\n");
		}
		status = (unsigned char)ft_atoi(ht_get(map, "?"));
		return (status);
	}
	while (1)
	{
		line = readline("minishell $> ");
		if (!line)
		{
			tputs("\033[A", 1, ft_putchar);
			tputs("minishell $> exit\n", 1, ft_putchar);
			return (0);
		}
		g_signal_int = 0;
		process_prompt(line, map);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_ht			map;
	char			*termtype;
	unsigned char	status;

	(void)argc;
	(void)argv;
	termtype = getenv("TERM");
	if (!termtype || tgetent(NULL, termtype) != 1)
	{
		ft_putendl_fd("Could not initialize termcap.", 2);
		return (1);
	}
//	disable_echoctl();
	setup_signals();
	ht_init_from_env(&map, envp);
	ht_set(&map, "?", "0");
	ht_set(&map, "OLDPWD", NULL);
	ht_set(&map, "0", "minishell");
	status = prompt_loop(&map);
	rl_clear_history();
	return (status);
}
