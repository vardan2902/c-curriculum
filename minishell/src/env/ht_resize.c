#include "minishell.h"

void	resize_map(t_ht *map)
{
	size_t		new_size;
	t_ht_node	**new_table;

	new_size = map->size * 2;
	new_table = create_new_table(new_size);
	rehash_nodes(map, new_table, new_size);
	free(map->table);
	map->table = new_table;
	map->size = new_size;
}

t_ht_node	**create_new_table(size_t size)
{
	t_ht_node	**new_table;

	new_table = (t_ht_node **)ft_calloc(size, sizeof (t_ht_node *));
	return (new_table);
}

void	rehash_nodes(t_ht *map, t_ht_node **new_table, size_t new_size)
{
	size_t		i;
	size_t		new_index;
	t_ht_node	*node;
	t_ht_node	*next;

	i = -1;
	while (++i < map->size)
	{
		node = map->table[i];
		while (node != NULL)
		{
			new_index = ht_hash(node->key, new_size);
			next = node->next;
			node->next = new_table[new_index];
			new_table[new_index] = node;
			node = next;
		}
	}
}

void	get_next_entry(t_ht_node *node, char **matrix, size_t *j)
{
	char	*tmp;

	while (node)
	{
		if (node->key && ft_strchr("#?", node->key[0]))
		{
			node = node->next;
			continue ;
		}
		if (!node->key || !node->value)
		{
			node = node->next;
			continue ;
		}
		tmp = ft_strjoin(node->key, "=");
		if (!tmp)
			return ;
		matrix[*j] = ft_strjoin(tmp, node->value);
		free(tmp);
		if (!matrix[*j])
			return ;
		++(*j);
		node = node->next;
	}
}

char	**ht_to_matrix(t_ht *map)
{
	char	**matrix;
	size_t  i;
	size_t  j;
	
	matrix = (char **)malloc((map->num_elements + 1) * sizeof(char *));
	if (!matrix)
		return (perror("malloc"), NULL);
	i = -1;
	j = 0;
	while (++i < map->size)
		get_next_entry(map->table[i], matrix, &j);
	matrix[j] = NULL;
	return (matrix);
}

void free_matrix(char **matrix)
{
	size_t	i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}
