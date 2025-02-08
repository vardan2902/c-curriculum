/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:22:32 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/08 17:31:40 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rev_rotate(t_dlst *stack)
{
	if (!stack->size)
		return ;
	stack->head = stack->head->prev;
}

void	rra(t_dstack *dstack, char mode)
{
	if (mode)
		ft_putstr_fd("rra\n", 1);
	rev_rotate(dstack->a);
}

void	rrb(t_dstack *dstack, char mode)
{
	if (mode)
		ft_putstr_fd("rrb\n", 1);
	rev_rotate(dstack->b);
}

void	rrr(t_dstack *dstack, char mode)
{
	if (mode)
		ft_putstr_fd("rrr\n", 1);
	rev_rotate(dstack->a);
	rev_rotate(dstack->b);
}
