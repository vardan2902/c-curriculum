#include "minishell.h"

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
	while (**prompt && !ft_isspace(**prompt)
		&& !ft_strchr("()&;|<> \t\r\v\f\n", **prompt))
	{
		if (!ft_isquote(**prompt))
			++(*prompt);
		else if (!tokenizer_handle_quotes(prompt, **prompt))
			return (NULL);
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
		if (*prompt == '#')
			while (*prompt)
				++prompt;
		if (!*prompt)
			break ;
		token = get_next_token(&prompt);
		if (!token)
			return (ft_lstclear(&token_lst, &del_token), NULL);
		new_node = ft_lstnew(token);
		if (!new_node)
		{
			ft_lstclear(&token_lst, &del_token);
			del_token((void *)token);
			return (NULL);
		}
		ft_lstadd_back(&token_lst, new_node);
	}
	return (token_lst);
}
