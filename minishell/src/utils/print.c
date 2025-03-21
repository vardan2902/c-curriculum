#include "minishell.h"

void	print_error(const char *prefix, const char *token, const char *sufix)
{
	ft_putstr_fd(prefix, STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd(sufix, STDERR_FILENO);
}

void	print_syntax_error(const char *token)
{
	print_error("minishell: syntax error near unexpected token `", token, "'");
}

static void	print_env_declare_list(t_ht *env)
{
	int		i;
	char	***env_entries;

	env_entries = ht_to_entries(env);
	i = -1;
	while (env_entries[++i])
	{
		printf("declare -x %s", env_entries[i][0]);
		if (env_entries[i][1])
			printf("=\"%s\"\n", env_entries[i][1]);
		else
			printf("\n");
		free(env_entries[i]);
	}
	free(env_entries);
}

static void	print_env_list(t_ht *env)
{
	int		i;
	char	**env_matrix;

	env_matrix = ht_to_matrix(env);
	i = -1;
	while (env_matrix[++i])
	{
		printf("%s\n", env_matrix[i]);
		free(env_matrix[i]);
	}
	free(env_matrix);
}

void	print_env(t_ht *env, int is_declare_list)
{
	if (is_declare_list)
		return (print_env_declare_list(env));
	return (print_env_list(env));
}
