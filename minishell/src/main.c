#include "minishell.h"

#include "minishell.h"
#include <stdio.h>

volatile sig_atomic_t	g_signal_int = 0;

/*
 * Helper: Convert token type to a human‐readable string.
 */
static const char	*token_type_to_str(int type)
{
	if (type == T_NONE)
		return ("NONE");
	else if (type == T_CMD)
		return ("CMD");
	else if (type == T_WORD)
		return ("WORD");
	else if (type == T_OR)
		return ("OR");
	else if (type == T_AND)
		return ("AND");
	else if (type == T_PIPE)
		return ("PIPE");
	else if (type == T_OPEN_PARENTHESIS)
		return ("OPEN_PARENTHESIS");
	else if (type == T_CLOSE_PARENTHESIS)
		return ("CLOSE_PARENTHESIS");
	else if (type == T_INPUT)
		return ("INPUT (<)");
	else if (type == T_OUTPUT)
		return ("OUTPUT (>)");
	else if (type == T_APPEND)
		return ("APPEND (>>)");
	else if (type == T_HEREDOC)
		return ("HEREDOC (<<)");
	return ("UNKNOWN");
}

/*
 * Recursively print the AST with indentation.
 */
void	print_ast(t_ast *ast, int indent)
{
	int i;
	int j;
	t_list *redir_it;
	t_redirection *redir;

	if (!ast)
		return;

	// Print indentation for the current node
	for (i = 0; i < indent; i++)
		printf("  ");
	printf("Node [%s]\n", token_type_to_str(ast->token));

	// If this is a command node, print its details
	if (ast->token == T_CMD && ast->cmd)
	{
		// Print command name
		for (i = 0; i < indent + 1; i++)
			printf("  ");
		printf("Command: %s\n", ast->cmd->name);

		// Print command arguments
		if (ast->cmd->args)
		{
			for (i = 0; i < indent + 1; i++)
				printf("  ");
			printf("Args: ");
			j = 0;
			while (ast->cmd->args[j])
			{
				printf("%s ", ast->cmd->args[j]);
				j++;
			}
			printf("\n");
		}

		// Print redirections
		if (ast->cmd->redirections)
		{
			for (i = 0; i < indent + 1; i++)
				printf("  ");
			printf("Redirections:\n");
			redir_it = ast->cmd->redirections;
			while (redir_it)
			{
				redir = (t_redirection *)redir_it->content;
				for (i = 0; i < indent + 2; i++)
					printf("  ");
				printf("[%s] -> %s\n", token_type_to_str(redir->type), redir->target);
				redir_it = redir_it->next;
			}
		}
	}

	// Print left subtree
	if (ast->left)
	{
		for (i = 0; i < indent + 1; i++)
			printf("  ");
		printf("Left:\n");
		print_ast(ast->left, indent + 2);
	}

	// Print right subtree
	if (ast->right)
	{
		for (i = 0; i < indent + 1; i++)
			printf("  ");
		printf("Right:\n");
		print_ast(ast->right, indent + 2);
	}
}

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
		print_ast(ast, 2);
	}
	rl_clear_history();
	return (0);
}
