/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:11:12 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/08 17:29:53 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_dlst *stack)
{
	t_node	*node1;
	t_node	*node2;
	int		num;

	if (!stack->head)
		return ;
	node1 = stack->head;
	node2 = node1->next;
	num = node1->num;
	node1->num = node2->num;
	node2->num = num;
	num = node1->pos;
	node1->pos = node2->pos;
	node2->pos = num;
}

void	sa(t_dstack *dstack, char mode)
{
	if (mode)
		ft_putstr_fd("sa\n", 1);
	swap(dstack->a);
}

void	sb(t_dstack *dstack, char mode)
{
	if (mode)
		ft_putstr_fd("sa\n", 1);
	swap(dstack->b);
}

void	ss(t_dstack *dstack, char mode)
{
	if (mode)
		ft_putstr_fd("ss\n", 1);
	swap(dstack->a);
	swap(dstack->b);
}
