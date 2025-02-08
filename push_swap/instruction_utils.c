/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:11:10 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/07 14:15:51 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	*not_combinable_inst(int count1, int count2, char *str1, char *str2)
{
	int		i;
	char	*result;
	char	*temp;

	result = NULL;
	i = -1;
	if (count1 == 0 && count2 == 0)
		return (ft_strdup(""));
	while (++i < count1 + count2)
	{
		if (!result)
			result = ft_strdup("");
		temp = result;
		if (i < count1)
			result = ft_strjoin(result, str1);
		else
			result = ft_strjoin(result, str2);
		if (temp)
			free(temp);
	}
	return (result);
}

static char	*combinable_inst(int count1, int count2, char *str1, char *str2)
{
	char	*comb;
	char	*result;

	comb = ft_strdup(str1);
	if (!comb)
		return (NULL);
	comb[ft_strlen(comb) - 2] = 'r';
	if (count1 > count2)
		result = not_combinable_inst(count2, count1 - count2, comb, str1);
	else
		result = not_combinable_inst(count1, count2 - count1, comb, str2);
	if (comb)
		free(comb);
	return (result);
}

static char	*specify_instruction(t_node *node, t_counter counter)
{
	int		rarb;
	int		rarrb;
	int		rrarb;
	int		rrarrb;

	rarb = max(counter.ra, counter.rb);
	rarrb = counter.ra + counter.rrb;
	rrarb = counter.rra + counter.rb;
	rrarrb = max(counter.rra, counter.rrb);
	if (node->move_count == rarb)
		return (combinable_inst(counter.ra, counter.rb, "ra ", "rb "));
	if (node->move_count == rarrb)
		return (not_combinable_inst(counter.ra, counter.rrb, "ra ", "rrb "));
	if (node->move_count == rrarb)
		return (not_combinable_inst(counter.rra, counter.rb, "rra ", "rb "));
	else if (node->move_count == rrarrb)
		return (combinable_inst(counter.rra, counter.rrb, "rra ", "rrb "));
	return (NULL);
}

char	*get_min_instruction(t_dstack *dstack, t_node *node)
{
	t_counter	counter;
	t_node		*curr;
	int			pos;

	curr = dstack->b->head;
	pos = 0;
	while (curr->pos != node->pos)
	{
		++pos;
		curr = curr->next;
	}
	fill_counter_data(dstack, &counter, curr, pos);
	return (specify_instruction(node, counter));
}
