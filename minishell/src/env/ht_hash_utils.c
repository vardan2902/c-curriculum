/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_hash_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:38:31 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/23 19:38:32 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ht_hash(const char *key, int size)
{
	size_t	hash;
	size_t	i;

	i = -1;
	hash = 0;
	while (++i < ft_strlen(key))
		hash = (hash + key[i]) % size;
	return (hash);
}

void	add_new_node(t_ht *map, size_t index,
			const char *key, void *value)
{
	t_ht_node	*new_node;

	new_node = (t_ht_node *)malloc(sizeof(t_ht_node));
	new_node->key = (char *)key;
	new_node->value = value;
	new_node->next = map->table[index];
	map->table[index] = new_node;
	map->num_elements += 1;
}

void	update_or_add_node(t_ht *map, unsigned int index,
			const char *key, void *value)
{
	t_ht_node	*node;

	node = map->table[index];
	while (node != NULL)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			free(node->key);
			free(node->value);
			node->key = (char *)key;
			node->value = value;
			return ;
		}
		node = node->next;
	}
	add_new_node(map, index, key, value);
}

t_ht_node	*find_node(t_ht *map, const char *key,
				t_ht_node **prev, size_t index)
{
	t_ht_node	*node;

	node = map->table[index];
	*prev = NULL;
	while (node != NULL)
	{
		if (ft_strcmp(node->key, key) == 0)
			return (node);
		*prev = node;
		node = node->next;
	}
	return (NULL);
}

void	remove_node(t_ht *map, t_ht_node *node, t_ht_node *prev, size_t index)
{
	if (prev == NULL)
		map->table[index] = node->next;
	else
		prev->next = node->next;
	free(node->key);
	free(node->value);
	free(node);
}
