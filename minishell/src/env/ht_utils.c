#include "minishell.h"

static void	get_next_pair(t_ht_node *node, char **matrix, size_t *j)
{
	char	*tmp;

	while (node)
	{
		if (node->key && (ft_strchr("#?", node->key[0])
				|| ft_isdigit(node->key[0])))
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
	size_t	i;
	size_t	j;

	matrix = (char **)malloc((map->num_elements + 1) * sizeof(char *));
	if (!matrix)
		return (perror("malloc"), NULL);
	i = -1;
	j = 0;
	while (++i < map->size)
		get_next_pair(map->table[i], matrix, &j);
	matrix[j] = NULL;
	return (matrix);
}

static void	s_sort_entries(char ***entries)
{
	int		min_index;
	char	**tmp;
	int		i;
	int		j;

	i = -1;
	while (entries[++i])
	{
		min_index = i;
		j = i;
		while (entries[++j])
			if (ft_strcmp(entries[min_index][0], entries[j][0]) > 0)
				min_index = j;
		tmp = entries[min_index];
		entries[min_index] = entries[i];
		entries[i] = tmp;
	}
}

static void	get_next_entry(t_ht_node *node, char ***entries, size_t *j)
{
	while (node)
	{
		if (node->key && (ft_strchr("#?", node->key[0])
				|| ft_isdigit(node->key[0])))
		{
			node = node->next;
			continue ;
		}
		entries[*j] = (char **)ft_calloc(2, sizeof (char *));
		entries[*j][0] = node->key;
		entries[*j][1] = node->value;
		++(*j);
		node = node->next;
	}
}

char	***ht_to_entries(t_ht *map)
{
	char	***entries;
	size_t	i;
	size_t	j;

	j = 0;
	entries = (char ***)malloc((map->num_elements + 1) * sizeof(char **));
	if (!entries)
		return (perror("malloc"), NULL);
	i = -1;
	while (++i < map->size)
		get_next_entry(map->table[i], entries, &j);
	entries[j] = NULL;
	s_sort_entries(entries);
	return (entries);
}
