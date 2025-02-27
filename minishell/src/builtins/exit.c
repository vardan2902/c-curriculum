#include "minishell.h"

static int	is_numeric(char *status)
{
	char	*trimmed;
	int		numeric;
	int		i;

	trimmed = ft_strtrim(status, " \t\n\v\r\f");
	i = 0;
	if (trimmed[i] == '+' || trimmed[i] == '-')
		++i;
	while (ft_isdigit(trimmed[i]))
		++i;
	numeric = (trimmed[i] == 0);
	free(trimmed);
	return (numeric);
}

int	ft_exit(char **args, t_ht *env)
{
	unsigned char	status;
	int				i;

	(void)env;
	i = 0;
	args += 1;
	ft_putendl_fd("exit", 2);
	while (args[i])
		++i;
	if (!*args)
		exit(0);
	if (*args && !is_numeric(*args))
	{
		ft_putendl_fd("minishell: exit: numeric argument required", 2);
		exit(255);
	}
	if (i > 1)
		return (ft_putendl_fd("minishell: exit: too many arguments", 2), 1);
	status = (unsigned char)ft_atoi(args[0]);
	exit(status);
	return (status);
}
