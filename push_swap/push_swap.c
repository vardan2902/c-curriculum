/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:41:48 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/08 18:08:54 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	initial_checks(int argc, char **argv, t_int_tab *tab)
{
	if (argc < 2)
		exit(0);
	parse_args(argc, argv, tab);
	if (is_tab_sorted(tab))
	{
		free(tab->arr);
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	t_int_tab	tab;
	t_dstack	*dstack;

	initial_checks(argc, argv, &tab);
	dstack = init_dstack(&tab);
	init_stack(dstack->a, &tab);
	free(tab.arr);
	sort_if_five(dstack);
	if (dstack->a->size > 3)
		push_to_b(dstack, tab);
	sort3(dstack->a);
	while (dstack->b->size > 0)
	{
		dstack->instructions = count_best_moves(dstack);
		execute(dstack);
	}
	final_order(dstack, 0);
	free_dstack(dstack);
	return (0);
}
