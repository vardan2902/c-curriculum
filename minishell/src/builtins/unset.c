#include "minishell.h"

static int	check_var_name(char *name)
{
	int	i;

	if (!name || ft_isdigit(name[0]))
		return (1);
	i = 0;
	while (name[i] && (ft_isalnum(name[i]) || name[i] == '_'))
		++i;
	return (name[i] != '\0');
}

static void	put_unset_error(char *name)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

int	ft_unset(char **args, t_ht *env)
{
	int	is_error;
	int	i;

	args += 1;
	is_error = 0;
	i = -1;
	while (args[++i])
	{
		if (check_var_name(args[i]))
		{
			put_unset_error(args[i]);
			is_error = 1;
		}
		else
			ht_remove_entry(env, args[i]);
	}
	return (is_error);
}
