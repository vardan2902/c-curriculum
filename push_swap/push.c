/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:14:29 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/08 17:30:17 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_dlst *from_stack, t_dlst *to_stack)
{
	t_node	*node;

	if (from_stack->size == 0)
		return ;
	node = from_stack->head;
	if (from_stack->size == 1)
		from_stack->head = NULL;
	else
	{
		from_stack->head = node->next;
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	--(from_stack->size);
	add_front(to_stack, node);
}

void	pa(t_dstack *dstack, char mode)
{
	if (mode)
		ft_putstr_fd("pa\n", 1);
	push(dstack->b, dstack->a);
}

void	pb(t_dstack *dstack, char mode)
{
	if (mode)
		ft_putstr_fd("pb\n", 1);
	push(dstack->a, dstack->b);
}
