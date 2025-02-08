/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:35:05 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/02 16:22:56 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*create_node(int n)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof (t_node));
	if (!node)
		return (NULL);
	node->num = n;
	node->pos = -1;
	node->move_count = 0;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	add_back(t_dlst *stack, t_node *new_node)
{
	t_node	*last;

	if (stack->size == 0)
	{
		stack->head = new_node;
		new_node->next = new_node;
		new_node->prev = new_node;
	}
	else
	{
		last = stack->head->prev;
		last->next = new_node;
		stack->head->prev = new_node;
		new_node->prev = last;
		new_node->next = stack->head;
	}
	++(stack->size);
}

void	add_front(t_dlst *stack, t_node *new_node)
{
	add_back(stack, new_node);
	stack->head = stack->head->prev;
}

void	add(t_dlst *stack, int value)
{
	t_node	*new_node;

	new_node = create_node(value);
	add_back(stack, new_node);
}

void	init_stack(t_dlst *stack, t_int_tab *tab)
{
	size_t	i;
	t_node	*min;
	t_node	*it;

	i = -1;
	while (++i < tab->size)
		add(stack, tab->arr[i]);
	i = -1;
	while (++i < stack->size)
	{
		it = stack->head;
		min = stack->head;
		while (it)
		{
			it = it->next;
			if (it == stack->head)
				break ;
			if ((min->pos != -1) || (min->num > it->num && it->pos == -1))
				min = it;
		}
		min->pos = i;
	}
}
