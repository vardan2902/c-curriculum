#include "minishell.h"

void	init_char_arr(t_char_arr *arr)
{
	arr->arr = NULL;
	arr->size = 0;
}

void	free_char_arr(t_char_arr *arr)
{
	size_t	i;

	i = 0;
	while (i < arr->size)
		free(arr->arr[i++]);
	free(arr->arr);
	arr->arr = NULL;
	arr->size = 0;
}

void	append_to_result(t_char_arr *arr, char *new_item)
{
	char	**tmp;
	size_t	i;

	tmp = (char **)malloc((arr->size + 2) * sizeof (char *));
	i = -1;
	while (++i < arr->size)
		tmp[i] = arr->arr[i];
	tmp[i++] = new_item;
	tmp[i] = NULL;
	free(arr->arr);
	arr->arr = tmp;
	++(arr->size);
}

void	split_and_append(t_char_arr *result, const char *str)
{
	char	**tokens;
	int		i;

	tokens = ft_split(str, ' ');
	if (!tokens)
		return ;
	i = -1;
	while (tokens[++i])
		append_to_result(result, tokens[i]);
	free(tokens);
}
