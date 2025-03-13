#include "minishell.h"

void	free_char_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

void	append_str(char **result, const char *str)
{
	char	*tmp;

	tmp = ft_strjoin(*result, str);
	free(*result);
	*result = tmp;
}
