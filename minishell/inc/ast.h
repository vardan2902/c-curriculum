#ifndef AST_H
# define AST_H

# include "minishell.h"

typedef enum e_cmd_token_types	t_cmd_token_types;
typedef enum e_redirections		t_redirections;
typedef struct s_cmd			t_cmd;
typedef struct s_ast			t_ast;


enum e_cmd_token_types
{
	NONE,
	WORD,
	CMD,
	PIPE,
	REDIRECT,
	AND,
	OR,
};

enum e_redirections
{
	TO,
	FROM,
	HEREDOC,
	APPEND,
}

struct s_cmd
{
	char				*cmd_name;
	char				**cmd_args;
}

struct s_ast
{
	t_ast_token_types	token;
	t_cmd				*cmd;
	t_ast				*left;
	t_ast				*right;
	t_redirections		redirection_mode;
	char				*redirection_path;
};

#endif



