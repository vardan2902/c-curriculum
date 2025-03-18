#include "minishell.h"

int	ft_unset(char **args, t_ht *env)
{
	int			is_error;
	int			i;

	args += 1;
	is_error = 0;
	i = -1;
	while (args[++i])
		ht_remove_entry(env, args[i]);
	return (is_error);
}
