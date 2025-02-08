/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_best_moves.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:23:45 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/03 14:48:15 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	set_move_count(t_node *node, t_counter counter)
{
	int	rarb;
	int	rarrb;
	int	rrarb;
	int	rrarrb;

	rarb = max(counter.ra, counter.rb);
	rarrb = counter.ra + counter.rrb;
	rrarb = counter.rra + counter.rb;
	rrarrb = max(counter.rra, counter.rrb);
	node->move_count = min_4(rarb, rarrb, rrarb, rrarrb);
}

static int	get_ra_count(t_dlst *stack, int pos)
{
	t_node	*curr;
	int		count;

	count = 0;
	curr = stack->head;
	while (curr->pos < pos || curr->prev->pos > pos)
	{
		curr = curr->next;
		++count;
	}
	return (count);
}

void	fill_counter_data(t_dstack *dstack, t_counter *counter, t_node *curr,
			int pos)
{
	counter->rb = pos;
	counter->rrb = dstack->b->size - pos;
	counter->ra = get_ra_count(dstack->a, curr->pos);
	counter->rra = dstack->a->size - counter->ra;
}

char	*count_best_moves(t_dstack *dstack)
{
	size_t		i;
	t_counter	counter;
	t_node		*curr;
	t_node		*min;

	curr = dstack->b->head;
	min = curr;
	i = -1;
	while (++i < dstack->b->size)
	{
		fill_counter_data(dstack, &counter, curr, i);
		set_move_count(curr, counter);
		curr = curr->next;
	}
	i = -1;
	while (++i < dstack->b->size)
	{
		if (curr->move_count < min->move_count)
			min = curr;
		curr = curr->next;
	}
	return (get_min_instruction(dstack, min));
}
