/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:42:53 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/08 18:07:58 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	get_instructions(t_dstack *dstack)
{
	char	*temp1;
	char	*temp2;

	while (1)
	{
		temp2 = dstack->instructions;
		temp1 = get_next_line(0);
		if (!temp1)
			break ;
		if (ft_strcmp("sa\n", temp1) && ft_strcmp("sb\n", temp1) && \
ft_strcmp("ss\n", temp1) && ft_strcmp("pa\n", temp1) && ft_strcmp("pb\n", \
temp1) && ft_strcmp("ra\n", temp1) && ft_strcmp("rb\n", temp1) && \
ft_strcmp("rr\n", temp1) && ft_strcmp("rra\n", temp1) && ft_strcmp("rrb\n", \
temp1) && ft_strcmp("rrr\n", temp1))
		{
			free_dstack(dstack);
			put_error();
		}
		if (!dstack->instructions)
			dstack->instructions = ft_strdup(temp1);
		else
			dstack->instructions = ft_strjoin(dstack->instructions, temp1);
		free(temp1);
		free(temp2);
	}
}

static void	check_is_sorted(t_dstack *dstack)
{
	t_node	*curr;
	int		pos;
	size_t	i;

	i = -1;
	pos = 0;
	if (dstack->b->size != 0)
		ft_putstr_fd("KO\n", 1);
	else
	{
		curr = dstack->a->head;
		while (++i < dstack->a->size)
		{
			if (curr->pos != pos)
				return (ft_putstr_fd("KO\n", 1));
			curr = curr->next;
			++pos;
		}
		ft_putstr_fd("OK\n", 1);
	}
}

static int	execute_rule(t_dstack *dstack, char *str)
{
	if (!ft_strcmp(str, "pa"))
		pa(dstack, 0);
	else if (!ft_strcmp(str, "pb"))
		pb(dstack, 0);
	else if (!ft_strcmp(str, "ra"))
		ra(dstack, 0);
	else if (!ft_strcmp(str, "rb"))
		rb(dstack, 0);
	else if (!ft_strcmp(str, "rr"))
		rr(dstack, 0);
	else if (!ft_strcmp(str, "rra"))
		rra(dstack, 0);
	else if (!ft_strcmp(str, "rrb"))
		rrb(dstack, 0);
	else if (!ft_strcmp(str, "rrr"))
		rrr(dstack, 0);
	else if (!ft_strcmp(str, "sa"))
		sa(dstack, 0);
	else if (!ft_strcmp(str, "sb"))
		sb(dstack, 0);
	else if (!ft_strcmp(str, "ss"))
		ss(dstack, 0);
	else
		return (0);
	return (1);
}

static int	execute_instructions(t_dstack *dstack)
{
	char	**instructions;
	int		i;
	int		has_finished;

	i = -1;
	has_finished = 1;
	instructions = ft_split(dstack->instructions, '\n');
	while (instructions[++i])
	{
		if (!execute_rule(dstack, instructions[i]))
		{
			has_finished = 0;
			break ;
		}
	}
	i = -1;
	while (instructions[++i])
		free(instructions[i]);
	free(instructions);
	free(dstack->instructions);
	dstack->instructions = NULL;
	return (has_finished);
}

int	main(int argc, char **argv)
{
	t_int_tab	tab;
	t_dstack	*dstack;

	if (argc < 2)
		return (0);
	parse_args(argc, argv, &tab);
	dstack = init_dstack(&tab);
	init_stack(dstack->a, &tab);
	free(tab.arr);
	get_instructions(dstack);
	if (!dstack->instructions)
		check_is_sorted(dstack);
	else if (execute_instructions(dstack))
		check_is_sorted(dstack);
	else
		ft_putstr_fd("Error\n", 1);
	free_dstack(dstack);
	return (0);
}
