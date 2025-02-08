/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:30:13 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/08 17:30:31 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*pop(t_dlst *stack)
{
	t_node	*node;

	if (!stack->size)
		return (NULL);
	if (stack->size == 1)
	{
		node = stack->head;
		stack->head = NULL;
		node->next = NULL;
		node->prev = NULL;
		--stack->size;
		return (node);
	}
	node = stack->head;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	stack->head = node->next;
	--stack->size;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
