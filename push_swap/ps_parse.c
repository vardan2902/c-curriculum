/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:32:46 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/07 20:50:11 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	check_empty_arg(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		while (ft_isspace(argv[i][j]))
			++j;
		if (argv[i][j] == '\0')
			put_error();
	}
}

static char	*join_args(int argc, char **argv)
{
	int		i;
	char	*ptr;
	char	*tmp;

	check_empty_arg(argc, argv);
	ptr = NULL;
	i = 0;
	while (++i < argc)
	{
		if (!ptr)
			ptr = ft_strdup(argv[i]);
		else
		{
			tmp = ft_strjoin(ptr, " ");
			free(ptr);
			if (!tmp)
				exit(0);
			ptr = ft_strjoin(tmp, argv[i]);
			free(tmp);
		}
		if (!ptr)
			exit(0);
	}
	return (ptr);
}

size_t	get_matrix_len(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i])
		++i;
	return (i);
}

static void	parse_matrix_to_tab(char **matrix, t_int_tab *tab)
{
	int	i;
	int	j;

	i = -1;
	while (matrix[++i])
	{
		j = -1;
		while (matrix[i][++j])
			if (!(ft_isdigit(matrix[i][j]) || matrix[i][j] == '+'
				|| matrix[i][j] == '-' || ft_isspace(matrix[i][j])))
				free_allocated(matrix, tab->arr);
		if (!check_int_limit(matrix[i]))
			free_allocated(matrix, tab->arr);
		tab->arr[i] = ft_atoi(matrix[i]);
	}
}

void	parse_args(int argc, char **argv, t_int_tab *tab)
{
	int		i;
	char	**matrix;
	char	*joined_args;

	i = 0;
	while (++i < argc)
		if (argv[i][0] == '\0')
			put_error();
	joined_args = join_args(argc, argv);
	matrix = ft_split(joined_args, ' ');
	free(joined_args);
	if (!matrix)
		exit(0);
	tab->size = get_matrix_len(matrix);
	tab->arr = (int *)malloc(tab->size * sizeof (int));
	if (!tab->arr)
	{
		free_arg_matrix(matrix);
		exit(0);
	}
	parse_matrix_to_tab(matrix, tab);
	free_arg_matrix(matrix);
	init_and_check_tab(tab);
}
