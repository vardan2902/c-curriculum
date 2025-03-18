#include "minishell.h"

bool	is_builtin(const char *cmd)
{
	bool		builtin;
	t_char_arr	expanded;
	char		*cmd_copy;

	cmd_copy = ft_strdup(cmd);
	init_char_arr(&expanded);
	expanded.size = 1;
	expanded.arr = &cmd_copy;
	remove_quotes(&expanded);
	builtin = (!ft_strcmp(cmd_copy, "echo") || !ft_strcmp(cmd_copy, "cd")
			|| !ft_strcmp(cmd_copy, "pwd") || !ft_strcmp(cmd_copy, "unset")
			|| !ft_strcmp(cmd_copy, "export") || !ft_strcmp(cmd_copy, "env")
			|| !ft_strcmp(cmd_copy, "exit"));
	return (builtin);
}
