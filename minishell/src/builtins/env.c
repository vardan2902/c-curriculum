#include "minishell.h"

int	ft_env(char **args, t_ht *env)
{
	int	i;

	i = 0;
	while (args[i])
		++i;
	if (i > 1)
	{
		print_error("env: ","","invalid arguments");
		return (1);
	}
	print_env(env, 0);
	return (0);
}
