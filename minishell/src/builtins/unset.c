#include "minishell.h"

static int	check_var_name(char *name)
{
	int	i;
 
 	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
 		return (1);
 	i = 0;
 	while (name[i] && (ft_isalnum(name[i]) || name[i] == '_'))
 		++i;
 	return (name[i] != '\0');
}

int	ft_unset(char **args, t_ht *env)
{
	int	i;

	args += 1;
	i = -1;
	while (args[++i])
	{
		if (check_var_name(args[i]))
			continue ;
		ht_remove_entry(env, args[i]);
	}
	return (0);
}
