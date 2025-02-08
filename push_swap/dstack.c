/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:17:09 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/08 17:11:12 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	free_tab_exit(t_int_tab *tab)
{
	if (tab->arr)
		free(tab->arr);
	exit(0);
}

t_dstack	*init_dstack(t_int_tab *tab)
{
	t_dstack	*dstack;

	dstack = (t_dstack *)malloc(sizeof (t_dstack));
	if (!dstack)
		free_tab_exit(tab);
	dstack->a = (t_dlst *)malloc(sizeof (t_dlst));
	dstack->b = (t_dlst *)malloc(sizeof (t_dlst));
	if (!dstack->a || !dstack->b)
	{
		if (dstack->a)
			free(dstack->a);
		if (dstack->b)
			free(dstack->b);
		free_tab_exit(tab);
	}
	dstack->a->head = NULL;
	dstack->b->head = NULL;
	dstack->a->size = 0;
	dstack->b->size = 0;
	dstack->instructions = NULL;
	return (dstack);
}

static void	free_dlst(t_dlst *dlst)
{
	if (!dlst)
		return ;
	while (dlst->size > 0)
		free(pop(dlst));
	free(dlst);
}

void	free_dstack(t_dstack *dstack)
{
	if (!dstack)
		return ;
	free_dlst(dstack->a);
	free_dlst(dstack->b);
	if (dstack->instructions)
		free(dstack->instructions);
	free(dstack);
}
