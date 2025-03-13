#include "minishell.h"

char	*get_lower_cmd(const char *cmd)
{
	size_t	i;
	size_t	len;
	char	*lower_cmd;

	if (!cmd)
		return (NULL);
	len = ft_strlen(cmd);
	lower_cmd = (char *)malloc((len + 1) * sizeof (char));
	if (!lower_cmd)
		return (NULL);
	i = -1;
	while (++i < len)
		lower_cmd[i] = ft_tolower(cmd[i]);
	lower_cmd[i] = '\0';
	return (lower_cmd);
}

bool	is_builtin(const char *cmd)
{
	char		*lower_cmd;
	bool		builtin;
	t_char_arr	expanded;

	lower_cmd = ft_strdup(cmd);
	init_char_arr(&expanded);
	expanded.size = 1;
	expanded.arr = &lower_cmd;
	remove_quotes(&expanded);
	lower_cmd = get_lower_cmd(*expanded.arr);
	if (!lower_cmd)
		return (false);
	builtin = (!ft_strcmp(lower_cmd, "echo") || !ft_strcmp(lower_cmd, "cd")
			|| !ft_strcmp(lower_cmd, "pwd") || !ft_strcmp(lower_cmd, "unset")
			|| !ft_strcmp(lower_cmd, "export") || !ft_strcmp(lower_cmd, "env")
			|| !ft_strcmp(lower_cmd, "exit"));
	free(lower_cmd);
	return (builtin);
}
