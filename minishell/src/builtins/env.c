#include "minishell.h"

int	ft_env(char **args, t_ht *env)
{
	char	**env_matrix;
	int		i;

	(void)args;
	env_matrix = ht_to_matrix(env);
	i = -1;
	while (env_matrix[++i])
	{
		printf("%s\n", env_matrix[i]);
		free(env_matrix[i]);
	}
	free(env_matrix);
	return (0);
}
