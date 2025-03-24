/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:39:59 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/23 19:41:06 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_ht_node(t_ht_node *node)
{
	free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

static void	ht_clear_slot(t_ht_node **lst)
{
	t_ht_node	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		del_ht_node(*lst);
		*lst = temp;
	}
}

void	ht_clear(t_ht *map)
{
	size_t	i;

	i = -1;
	while (++i < map->size)
		ht_clear_slot(&map->table[i]);
	free(map->table);
}
