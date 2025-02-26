#include "minishell.h"

int	ft_echo(char **args, t_ht *env)
{
	int	i;
	int	j;
	int	print_nl;

	(void)env;
	args += 1;
	i = -1;
	print_nl = -1;
	while (args[++i])
	{
		j = 0;
		if (args[i][j] != '-')
			break ;
		while (args[i][++j] == 'n')
			continue ;
		if (args[i][j] != '\0')
			break ;
		print_nl = i;
	}
	i = print_nl;
	while (args[++i])
	{
		if (i > print_nl + 2)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(args[i], 1);
	}
	if (print_nl == -1)
		ft_putchar_fd('\n', 1);
	return (0);
}
