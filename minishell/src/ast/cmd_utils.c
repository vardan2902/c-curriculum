#include "minishell.h"

bool	is_builtin(const char *cmd)
{
	bool		builtin;

	builtin = (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
			|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "unset")
			|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "env")
			|| !ft_strcmp(cmd, "exit"));
	return (builtin);
}
