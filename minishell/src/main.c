#include "minishell.h"

extern volatile sig_atomic_t	g_signal_int;

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
	status = ft_itoa((unsigned char)execute_ast(ast, map));
	ht_set(map, "?", status);
}

void	prompt_loop(t_ht *map)
{
	char	*line;

	while (1)
	{
		line = readline("minishell $> ");
		if (!line)
		{
			tputs("\033[A", 1, ft_putchar);
			tputs("minishell $> exit\n", 1, ft_putchar);
			return ;
		}
		g_signal_int = 0;
		process_prompt(line, map);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_ht	map;
	char	*termtype;

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
	prompt_loop(&map);
	rl_clear_history();
	return (0);
}
