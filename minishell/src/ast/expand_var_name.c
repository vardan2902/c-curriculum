#include "minishell.h"

static char	*extract_var_name(const char *token, int *i)
{
	int		start;
	int		len;
	char	*var_name;

	start = *i + 1;
	if (token[start] == '?')
		return (*i = start, ft_strdup("?"));
	if (token[start] == '$')
		return (*i = start, ft_strdup("$"));
	len = 0;
	while (ft_isalnum(token[start + len]) || token[start + len] == '_')
		len++;
	if (len == 0)
		return (NULL);
	var_name = ft_substr(token, start, len);
	if (!var_name)
		return (NULL);
	*i = start + len - 1;
	return (var_name);
}

void	expand_variable(const char *token, int *i, char **current, t_ht *env)
{
	char	*key;
	char	*value;

	key = extract_var_name(token, i);
	if (!key)
		return ;
	value = ht_get(env, key);
	if (value)
		append_str(current, value);
	free(key);
}
