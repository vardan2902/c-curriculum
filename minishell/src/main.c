#include "minishell.h"

#include "minishell.h"
#include <stdio.h>

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



int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	t_ht	map;
	char	*line;
	t_list	*token_lst;
	t_ast	*ast;

	ht_init_from_env(&map, envp);
	while (1)
	{
		line = readline("minishell $>");
		if (line && *line)
		{
			token_lst = get_token_lst(line);
			if (!token_lst)
				continue ;
			ast = ast_create_from_tokens(&token_lst, 0);
			if (!ast)
				continue ;
			print_ast(ast, 2);
		}
	}
		(void)ast;
	return (0);
}
