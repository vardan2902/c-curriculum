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
	size_t		i;

	i = -1;
	new_table = (t_ht_node **)malloc(sizeof(t_ht_node *) * size);
	while (++i < size)
		new_table[i] = NULL;
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

// TODO: fix
char **ht_to_matrix(t_ht *map)
{
	char	**matrix;
	size_t  i;
	size_t  j = 0;
	size_t  total = map->num_elements;
	
	matrix = malloc((total + 1) * sizeof(char *));
	if (!matrix)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < map->size; i++)
	{
		t_ht_node *node = map->table[i];
		while (node)
		{
			size_t key_len = ft_strlen(node->key);
			size_t value_len = ft_strlen((char *)node->value);
			size_t len = key_len + value_len + 2;

			matrix[j] = malloc(len * sizeof(char));
			if (!matrix[j])
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			snprintf(matrix[j], len, "%s=%s", node->key, (char *)node->value);
			j++;
			node = node->next;
		}
	}
	matrix[j] = NULL;
	return matrix;
}

void free_matrix(char **matrix)
{
	size_t i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}
