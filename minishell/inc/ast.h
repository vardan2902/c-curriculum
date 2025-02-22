#ifndef AST_H
# define AST_H

# include "minishell.h"

typedef struct s_cmd			t_cmd;
typedef struct s_ast			t_ast;

struct s_cmd
{
	char				*name;
	char				**args;
};

struct s_ast
{
	t_cmd_token_types	token;
	t_cmd				*cmd;
	t_ast				*left;
	t_ast				*right;
	t_redirections		redirection_mode;
	char				*redirection_path;
};

t_ast	*ast_create_from_tokens(t_list **token_lst);

#endif
