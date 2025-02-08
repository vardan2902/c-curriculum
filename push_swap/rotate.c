/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:19:47 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/08 17:31:21 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_dlst *stack)
{
	if (!stack->size)
		return ;
	stack->head = stack->head->next;
}

void	ra(t_dstack *dstack, char mode)
{
	if (mode)
		ft_putstr_fd("ra\n", 1);
	rotate(dstack->a);
}

void	rb(t_dstack *dstack, char mode)
{
	if (mode)
		ft_putstr_fd("rb\n", 1);
	rotate(dstack->b);
}

void	rr(t_dstack *dstack, char mode)
{
	if (mode)
		ft_putstr_fd("rr\n", 1);
	rotate(dstack->a);
	rotate(dstack->b);
}
