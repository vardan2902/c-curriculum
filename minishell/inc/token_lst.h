#ifndef TOKEN_LST_H
# define TOKEN_LST_H

# include "minishell.h"

typedef struct s_token	t_token;

struct s_token
{
	char				*value;
	t_cmd_token_types	type;
};

t_list	*get_token_lst(char *prompt);
void	del_token(void *args);
void	skip_whitespaces(char **str);
t_token	*create_token(char *value, t_cmd_token_types type);
t_token	*get_operator_token(char **prompt);
size_t	tokenizer_handle_quotes(char **prompt, char quote);

#endif
