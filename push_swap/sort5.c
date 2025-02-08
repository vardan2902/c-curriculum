/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_if_five.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:22:28 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/03 14:41:51 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_min_pos(t_dlst *stack)
{
	size_t	i;
	int		min_pos;
	t_node	*node;

	i = -1;
	node = stack->head;
	min_pos = node->pos;
	while (++i < stack->size)
	{
		if (node->pos < min_pos)
			min_pos = node->pos;
		node = node->next;
	}
	return (min_pos);
}

void	push_first2_to_b(t_dstack *dstack)
{
	size_t	i;

	i = -1;
	while (++i < 5 && dstack->b->size < 2)
	{
		if (dstack->a->head->pos == 0 || dstack->a->head->pos == 1)
			pb(dstack, 1);
		else
			ra(dstack, 1);
	}
	if (dstack->b->head->pos == 0)
		rb(dstack, 1);
}

static void	sort5(t_dstack *dstack)
{
	push_first2_to_b(dstack);
	sort3(dstack->a);
	final_order(dstack, get_min_pos(dstack->a));
	pa(dstack, 1);
	pa(dstack, 1);
}

void	sort_if_five(t_dstack *dstack)
{
	if (dstack->a->size != 5)
		return ;
	sort5(dstack);
	exit(0);
}
