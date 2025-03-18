#ifndef AST_H
# define AST_H

# include "minishell.h"

typedef struct s_cmd			t_cmd;
typedef struct s_redirection	t_redirection;
typedef struct s_ast			t_ast;
typedef struct s_char_arr		t_char_arr;

struct s_redirection
{
	t_cmd_token_types	type;
	char				*target;
};

struct s_cmd
{
	char	*name;
	char	**args;
	t_list	*redirections;
};

struct s_char_arr
{
	char	**arr;
	size_t	size;
};

struct s_ast
{
	t_cmd_token_types	token;
	t_cmd				*cmd;
	t_ast				*left;
	t_ast				*right;
	int					indent;
	bool				is_subshell;
};

t_ast		*ast_create_from_tokens(t_list **token_lst, int indent);
int			execute_ast(t_ast *node, t_ht *env);
int			get_precedence(int token);
t_ast		*ast_create_root(void);
int			is_redir(t_cmd_token_types type);
int			is_word_or_redir(t_cmd_token_types type);
int			is_operation(t_cmd_token_types type);
int			ast_add_redirection(t_cmd *cmd, t_list **token_lst, t_list *prev);
int			ast_add_cmd(t_ast *it, t_list **token_lst);
int			handle_redirections_and_restore(t_list *redirections,
			t_ht *env, int saved_stdin, int saved_stdout);
int			exec_builtin(t_ast *node, t_ht *env);
char		*extract_var_name(const char *token, int *i);
t_char_arr	*expand_text(const char *token, t_ht *env);
void		expand_wildcards(t_char_arr *result);
void		remove_quotes(t_char_arr *result);
void		append_to_result(t_char_arr *arr, char *new_item);
int			handle_redirections(t_list *redir_lst, t_ht *env, int saved_stdin);

void		append_str(char **result, const char *str);

int		execute_pipe(t_ast *node, t_ht *env);


void	init_char_arr(t_char_arr *arr);
void	free_char_arr(t_char_arr *arr);
void	*ft_free(void *ptr);

void	free_char_matrix(char **matrix);
void	append_str(char **result, const char *str);
void	append_to_result(t_char_arr *arr, char *new_item);
void	split_and_append(t_char_arr *result, const char *str);
bool 	is_builtin(const char *cmd);
char	*build_cmd_path(char *cmd, t_ht *env, int *status);

#endif
