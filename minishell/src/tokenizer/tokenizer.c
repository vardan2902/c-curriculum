#include "minishell.h"

void	skip_whitespaces(char **str)
{
	while (ft_isspace(**str))
		++(*str);
}

static void	del_token(void *args)
{
	t_token	*token;

	token = (t_token *)args;
	if (!token || !token->value)
		return ;
	free(token->value);
	free(token);
}

t_token	*create_token(char *value, t_cmd_token_types type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof (t_token));
	if (!token)
		return (free(value), NULL);
	token->value = value;
	token->type = type;
	return (token);
}

t_token	*get_operator_token(char **prompt)
{
	if (ft_strncmp(*prompt, "||", 2) == 0)
		return ((*prompt) += 2, create_token(ft_strdup("||"), T_OR));
	if (ft_strncmp(*prompt, "&&", 2) == 0)
		return ((*prompt) += 2, create_token(ft_strdup("&&"), T_AND));
	if (ft_strncmp(*prompt, "<<", 2) == 0)
		return ((*prompt) += 2, create_token(ft_strdup("<<"), T_HEREDOC));
	if (ft_strncmp(*prompt, ">>", 2) == 0)
		return ((*prompt) += 2, create_token(ft_strdup(">>"), T_APPEND));
	if (**prompt == '|')
		return (++(*prompt), create_token(ft_strdup("|"), T_PIPE));
	if (**prompt == '>')
		return (++(*prompt), create_token(ft_strdup(">"), T_OUTPUT));
	if (**prompt == '<')
		return (++(*prompt), create_token(ft_strdup("<"), T_INPUT));
	if (**prompt == '(')
		return (++(*prompt), create_token(ft_strdup("("), T_OPEN_PARENTHESIS));
	if (**prompt == ')')
		return (++(*prompt), create_token(ft_strdup(")"), T_CLOSE_PARENTHESIS));
	return (NULL);
}

size_t	handle_quotes(char **prompt, char quote)
{
	char	*start;

	start = *prompt;
	++(*prompt);
	while (**prompt && **prompt != quote)
		++(*prompt);
	if (**prompt != quote)
		return (0);
	++(*prompt);
	return (*prompt - start);
}

t_token	*get_next_token(char **prompt)
{
	char	*start;
	char	*value;
	t_token	*token;

	start = *prompt;
	if (**prompt == '\0')
		return (NULL);
	token = get_operator_token(prompt);
	if (token)
		return (token);
	if (**prompt == '&')
		return (NULL);
	while (**prompt && !ft_isspace(**prompt) && !ft_strchr("()&|<># \t\r\v\f\n", **prompt))
	{
		if (**prompt == '"' || **prompt == '\'')
		{
		   if (!handle_quotes(prompt, **prompt))
			   return (NULL);
		}
		else
			++(*prompt);
	}
	value = ft_substr(start, 0, *prompt - start);
	if (!value)
		return (NULL);
	return (create_token(value, T_WORD));
}

t_list	*get_token_lst(char *prompt)
{
	t_list	*token_lst;
	t_list	*new_node;
	t_token	*token;

	token_lst = NULL;
	while (*prompt)
	{
		skip_whitespaces(&prompt);
		if (!*prompt)
			break ;
		if (*prompt == '#')
		{
			while (*prompt)
				++prompt;
			break ;
		}
		token = get_next_token(&prompt);
		if (!token)
			return (ft_lstclear(&token_lst, &del_token), NULL);
		new_node = ft_lstnew(token);
		if (!new_node)
			return (ft_lstclear(&token_lst, &del_token), del_token((void *)token), NULL);
		ft_lstadd_back(&token_lst, new_node);
	}
	return (token_lst);
}
