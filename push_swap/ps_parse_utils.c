/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:18:43 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/07 14:20:56 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_int_limit(const char *str)
{
	size_t			i;
	int				sign;
	long long int	num;
	int				seen;

	i = 0;
	sign = 1;
	num = 0;
	seen = 0;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (ft_isdigit(str[i]))
	{
		seen = 1;
		num = num * 10 + str[i++] - '0';
		if ((num * sign) > INT_MAX || (num * sign) < INT_MIN)
			return (0);
	}
	if (str[i] || !seen)
		return (0);
	return (1);
}

int	contains_duplicates(t_int_tab *tab)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < tab->size - 1)
	{
		j = i;
		while (++j < tab->size)
			if (tab->arr[i] == tab->arr[j])
				return (1);
	}
	return (0);
}

int	is_tab_sorted(t_int_tab *tab)
{
	size_t	i;

	i = -1;
	while (++i < tab->size - 1)
		if (tab->arr[i] > tab->arr[i + 1])
			return (0);
	return (1);
}

void	free_arg_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix && matrix[++i])
		free(matrix[i]);
	if (matrix)
		free(matrix);
}

void	free_allocated(char **matrix, int *arr)
{
	free_arg_matrix(matrix);
	if (arr)
		free(arr);
	put_error();
}
