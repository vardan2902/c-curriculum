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
	token->quoting_state = Q_NONE;
	return (token);
}

t_token	*create_token_with_state(char *value, t_cmd_token_types type,
	t_quoting_state state)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof (t_token));
	if (!token)
		return (free(value), NULL);
	token->value = value;
	token->type = type;
	token->quoting_state = state;
	return (token);
}

t_token	*get_operator_token(char **prompt)
{
	if (ft_strncmp(*prompt, "||", 2) == 0)
		return ((*prompt) += 2, create_token(ft_strdup("||"), T_OR));
	if (ft_strncmp(*prompt, "&&", 2) == 0)
		return ((*prompt) += 2, create_token(ft_strdup("&&"), T_AND));
	if (ft_strncmp(*prompt, "<<", 2) == 0)
		return ((*prompt) += 2, create_token(ft_strdup("<<"), T_REDIRECT));
	if (ft_strncmp(*prompt, ">>", 2) == 0)
		return ((*prompt) += 2, create_token(ft_strdup(">>"), T_REDIRECT));
	if (**prompt == '|')
		return (++(*prompt), create_token(ft_strdup("|"), T_PIPE));
	if (**prompt == '>')
		return (++(*prompt), create_token(ft_strdup(">"), T_REDIRECT));
	if (**prompt == '<')
		return (++(*prompt), create_token(ft_strdup("<"), T_REDIRECT));
	if (**prompt == '(')
		return (++(*prompt), create_token(ft_strdup("("), T_OPEN_PARENTHESIS));
	if (**prompt == ')')
		return (++(*prompt), create_token(ft_strdup(")"), T_CLOSE_PARENTHESIS));
	return (NULL);
}

t_token	*get_variable_token(char **prompt, t_ht *ht_env)
{
	char	*start;
	char	*key;
	char	*value;

	if (**prompt != '$')
		return (NULL);
	++(*prompt);
	start = *prompt;
	if (**prompt == '?')
		return (++(*prompt), create_token(ft_strdup("$?"), T_WORD));
	while (ft_isalnum(**prompt) || **prompt == '_')
		++(*prompt);
	key = ft_substr(start, 0, *prompt - start);
	if (!key)
		return (NULL);
	value = ht_get(ht_env, key);
	free(key);
	if (!value)
		return (NULL);
	return (create_token(value, T_WORD));
}

char *append_variable_value(char **prompt, char *word, size_t *len, t_ht *ht_env)
{
	char	*start;
	char	*key;
	char	*value;
	char	*new_word;

	++(*prompt);
	start = *prompt;
	while (ft_isalnum(**prompt) || **prompt == '_')
		++(*prompt);
	key = ft_substr(start, 0, *prompt - start);
	if (!key)
		return (NULL);
	value = ht_get(ht_env, key);
	free(key);
	if (!value)
		return (NULL);
	if (value)
	{
		new_word = ft_strjoin(word, value);
		free(word);
		if (!new_word)
			return (NULL);
		word = new_word;
		*len += ft_strlen(value);
	}
	free(value);
	return (word);
}

char	*append_regular_character(char **prompt, char *word, size_t *len)
{
	char	*new_word;

	if (!**prompt)
		return (NULL);
	new_word = (char *)ft_calloc(*len + 2, sizeof (char));
	if (!new_word)
		return (NULL);
	ft_strlcpy(new_word, word, *len + 1);
	new_word[*len] = **prompt;
	new_word[*len + 1] = '\0';
	free(word);
	++(*len);
	++(*prompt);
	return (new_word);
}

t_token	*handle_double_quotes(char **prompt, t_ht *ht_env)
{
	char	*word;
	size_t	len;

	++(*prompt);
	len = 0;
	word = (char *)ft_calloc(1, sizeof (char));
	if (!word)
		return (NULL);
	while (**prompt && **prompt != '"')
	{
		if (**prompt == '$')
			word = append_variable_value(prompt, word, &len, ht_env);
		else
			word = append_regular_character(prompt, word, &len);
		if (!word)
			return (NULL);
	}
	if (**prompt == '"')
		++(*prompt);
	else
		return (free(word), NULL);
	return (create_token_with_state(word, T_WORD, Q_DOUBLE));
}

t_token	*handle_single_quotes(char **prompt)
{
	char	*start;
	char	*value;

	++(*prompt);
	start = *prompt;
	while (**prompt && **prompt != '\'')
		++(*prompt);
	if (**prompt != '\'')
		return (NULL);
	value = ft_substr(start, 0, *prompt - start);
	if (!value)
		return (NULL);
	++(*prompt);
	return (create_token_with_state(value, T_WORD, Q_SINGLE));
}

t_token	*get_next_token(char **prompt, t_ht *ht_env)
{
	char	*start;
	char	*value;
	t_token	*token;

	skip_whitespaces(prompt);
	start = *prompt;
	if (**prompt == '\0')
		return (NULL);
	token = get_operator_token(prompt);
	if (token)
		return (token);
	if (**prompt == '&')
		return (NULL);
	token = get_variable_token(prompt, ht_env);
	if (token)
		return (token);
	while (**prompt && !ft_isspace(**prompt) && !ft_strchr("()&|<>", **prompt))
	{
		if (**prompt == '"')
			return (handle_double_quotes(prompt, ht_env));
		if (**prompt == '\'')
			return (handle_single_quotes(prompt));
		++(*prompt);
	}	
	value = ft_substr(start, 0, *prompt - start);
	if (!value)
		return (NULL);
	return (create_token(value, T_WORD));
}

t_list	*get_token_lst(char *prompt, t_ht *ht_env)
{
	t_list	*token_lst;
	t_list	*new_node;
	t_token	*token;

	token_lst = NULL;
	while (*prompt)
	{
		token = get_next_token(&prompt, ht_env);
		if (!token)
			return (ft_lstclear(&token_lst, &del_token), NULL);
		new_node = ft_lstnew(token);
		if (!new_node)
			return (ft_lstclear(&token_lst, &del_token), del_token((void *)token), NULL);
		ft_lstadd_back(&token_lst, new_node);
	}
	return (token_lst);
}
