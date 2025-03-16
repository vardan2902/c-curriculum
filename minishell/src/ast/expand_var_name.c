#include "minishell.h"

char	*extract_var_name(const char *token, int *i)
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
