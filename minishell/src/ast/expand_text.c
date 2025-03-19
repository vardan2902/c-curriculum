#include "minishell.h"

static void	handle_quotes(const char token, bool *in_single_quotes,
	bool *in_double_quotes)
{
	if (token == '\'' && !(*in_double_quotes))
		*in_single_quotes = !(*in_single_quotes);
	else if (token == '"' && !(*in_single_quotes))
		*in_double_quotes = !(*in_double_quotes);
}

static t_char_arr	*init_expansion(char **current)
{
	t_char_arr	*result;

	result = ft_calloc(1, sizeof(t_char_arr));
	if (!result)
		return (NULL);
	*current = ft_strdup("");
	if (!*current)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

static void	update_current_after_split(t_char_arr *result, char **current, int last_space)
{
	if (result->size > 0 && !last_space)
	{
		free(*current);
		*current = result->arr[result->size - 1];
		result->size--;
	}
	else
	{
		free(*current);
		*current = ft_strdup("");
	}
}

static void	handle_tilde_expansion(const char *token, int i,
	char **current, t_ht *env)
{
	char	*identifier;
	char	*home;

	home = ht_get(env, "HOME");
	if (!home)
		return ;
	if (i == 0)
	{
		free(*current);
		*current = ft_strdup(home);
	}
	else if (i > 0 && token[i - 1] == '=')
	{
		identifier = ft_substr(*current, 0, ft_strlen(*current) - 1);
		if (is_valid_identifier(identifier, 0))
			append_str(current, home);
		else
			append_str(current, "~");
		free(identifier);
	}
}

static void	handle_regular_char(char token_char, char **current)
{
	char	str[2];

	str[0] = token_char;
	str[1] = '\0';
	append_str(current, str);
}

static void	split_and_update(char **current, t_char_arr *result, int last_space)
{
	split_and_append(result, *current);
	update_current_after_split(result, current, last_space);
}

static int	is_last_space(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0)
		return (ft_isspace(str[len - 1]));
	return (0);
}

static void	expand_symbols(const char *token, char **current,
	t_char_arr *result, t_ht *env)
{
	bool	in_single;
	bool	in_double;
	char	*var_key;
	char	*var_value;
	int		i;

	in_single = false;
	in_double = false;
	i = -1;
	while (token && token[++i])
	{
		handle_quotes(token[i], &in_single, &in_double);
		if (!token[i])
			break ;
		if (token[i] == '$' && !in_single)
		{
			char	str[2];
			
			if (!token[i + 1] || (!ft_isalnum(token[i + 1]) && !ft_strchr("_?\"'", token[i + 1]))
				|| (in_double && ft_isquote(token[i + 1])))
			{
				str[0] = token[i];
				str[1] = '\0';
				append_str(current, str);
				continue ;
			}
			var_key = extract_var_name(token, &i);
			if (!var_key)
				continue ;
			var_value = ht_get(env, var_key);
			free (var_key);
			if (!var_value)
				continue ;
			append_str(current, var_value);
			if (!in_double)
				split_and_update(current, result, is_last_space(var_value));
		}
		else if (token[i] == '~' && (token[i + 1] == '/' || !token[i + 1]))
			handle_tilde_expansion(token, i, current, env);
		else
			handle_regular_char(token[i], current);
	}
}

t_char_arr	*expand_text(const char *token, t_ht *env)
{
	t_char_arr	*result;
	char		*current;

	result = init_expansion(&current);
	if (!result)
		return (NULL);
	expand_symbols(token, &current, result, env);
	if (current[0] != '\0')
		append_to_result(result, current);
	else
		free(current);
	return (result);
}
