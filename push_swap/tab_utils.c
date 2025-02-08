/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:39:03 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/07 20:51:40 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_and_check_tab(t_int_tab *tab)
{
	tab->max = tab->size - 1;
	tab->min = 0;
	tab->mid = tab->size / 2;
	if (contains_duplicates(tab))
	{
		free(tab->arr);
		put_error();
	}
}

void	sort3(t_dlst *stack)
{
	if ((stack->head->pos < stack->head->next->pos)
		&& (stack->head->next->pos < stack->head->prev->pos))
		return ;
	if ((stack->head->pos < stack->head->next->pos)
		&& (stack->head->pos > stack->head->prev->pos))
		return ;
	if ((stack->head->next->pos < stack->head->prev->pos)
		&& (stack->head->prev->pos < stack->head->pos))
		return ;
	swap(stack);
	ft_putstr_fd("sa\n", 1);
}

void	push_to_b(t_dstack *dstack, t_int_tab tab)
{
	size_t	i;
	size_t	j;
	size_t	size;

	size = dstack->a->size;
	i = -1;
	while (++i < size)
	{
		j = dstack->a->head->pos;
		if (j == tab.max || j == tab.min || j == tab.mid)
			ra(dstack, 1);
		else
			pb(dstack, 1);
	}
}
