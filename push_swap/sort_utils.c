/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:04:30 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/08 17:22:07 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_rule(t_dstack *dstack, char *str)
{
	if (!ft_strcmp(str, "ra"))
		ra(dstack, 1);
	else if (!ft_strcmp(str, "rb"))
		rb(dstack, 1);
	else if (!ft_strcmp(str, "rr"))
		rr(dstack, 1);
	else if (!ft_strcmp(str, "rra"))
		rra(dstack, 1);
	else if (!ft_strcmp(str, "rrb"))
		rrb(dstack, 1);
	else if (!ft_strcmp(str, "rrr"))
		rrr(dstack, 1);
}

void	execute(t_dstack *dstack)
{
	char	**instructions;
	int		i;

	instructions = ft_split(dstack->instructions, ' ');
	if (!instructions)
	{
		free(dstack->instructions);
		dstack->instructions = NULL;
		return ;
	}
	i = -1;
	while (instructions && instructions[++i])
		do_rule(dstack, instructions[i]);
	i = -1;
	while (instructions[++i])
		free(instructions[i]);
	free(instructions);
	free(dstack->instructions);
	dstack->instructions = NULL;
	pa(dstack, 1);
}

void	final_order(t_dstack *dstack, int min)
{
	size_t	req_moves;
	t_node	*node;

	req_moves = 0;
	node = dstack->a->head;
	while (node->pos != min)
	{
		++req_moves;
		node = node->next;
	}
	if (req_moves <= dstack->a->size / 2)
		while (req_moves-- > 0)
			ra(dstack, 1);
	else
	{
		req_moves = dstack->a->size - req_moves;
		while (req_moves-- > 0)
			rra(dstack, 1);
	}
}
