#include "minishell.h"

int	ft_env(char **args, t_ht *env)
{
	(void)args;
	print_env(env, 0);
	return (0);
}
