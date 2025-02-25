#include "minishell.h"

#include "minishell.h"
#include <stdio.h>

volatile sig_atomic_t	g_signal_int = 0;

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void disable_echoctl(void) {
    struct termios term;

    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        perror("tcgetattr");
        return;
    }
    term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1) {
        perror("tcsetattr");
    }
}

void handle_sigint(int signum)
{
	(void)signum;
	g_signal_int = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

void setup_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	disable_echoctl();
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	t_ht	map;
	char	*line;
	t_list	*token_lst;
	t_ast	*ast;	
	char	*termtype;

	termtype = getenv("TERM");
    if (!termtype || tgetent(NULL, termtype) != 1) {
        fprintf(stderr, "Could not initialize termcap.\n");
        return 1;
    }
	setup_signals(); 
	ht_init_from_env(&map, envp);
	while (1)
	{
		line = readline("minishell $> ");
		if (!line)
		{
			tputs("\033[A", 1, ft_putchar);
			tputs("minishell $> exit\n", 1, ft_putchar);
			break ;
		}
		g_signal_int = 0;
		if (!*line)
		{
			free(line);
			continue ;
		}
		add_history(line);
		token_lst = get_token_lst(line);
		free(line);
		if (!token_lst)
			continue ;
		ast = ast_create_from_tokens(&token_lst, 0);
		if (!ast)
			continue ;
		execute_ast(ast, &map);
	}
	rl_clear_history();
	return (0);
}
