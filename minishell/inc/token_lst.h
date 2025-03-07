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

#endif
