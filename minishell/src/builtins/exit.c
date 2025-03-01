#include "minishell.h"

int	check_int_limit(const char *str)
{
	size_t			i;
	int				sign;
	long long int	num;
	int				seen;
	int				prev_num;

	i = 0;
	sign = 1;
	num = 0;
	seen = 0;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (ft_isdigit(str[i]))
	{
		seen = 1;
		prev_num = num;
		num = num * 10 + str[i++] - '0';
		if ((sign == 1 && num < prev_num) || (sign == -1 && num > prev_num))
			return (0);
	}
	if (str[i] || !seen)
		return (0);
	return (1);
}

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
	numeric = (check_int_limit(trimmed) && trimmed[i] == 0);
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
	if (!ht_get(env, "#IS_SUBSHELL"))
		ft_putendl_fd("exit", 1);
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
