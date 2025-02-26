#include "minishell.h"

int	ft_pwd(char **args, t_ht *env)
{
	char	cwd[PATH_MAX];	
	
	(void)args;
	(void)env;
	if (getcwd(cwd, sizeof (cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("minishell: pwd");
	
	return (0);
}
