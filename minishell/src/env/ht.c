#include "minishell.h"

void	ht_init_map(t_ht *map, size_t size)
{
	size_t	i;

	map->table = (t_ht_node **)malloc(sizeof(t_ht_node *) * size);
	i = -1;
	while (++i < size)
		map->table[i] = NULL;
	map->size = size;
	map->num_elements = 0;
}

void	ht_set(t_ht *map, const char *key, char *value)
{
	size_t	index;

	if (map->num_elements >= map->size * 0.7)
		resize_map(map);
	index = ht_hash(key, map->size);
	update_or_add_node(map, index, key, value);
}

char	*ht_get(t_ht *map, const char *key)
{
	size_t		index;
	t_ht_node	*node;

	index = ht_hash(key, map->size);
	node = map->table[index];
	while (node != NULL)
	{
		if (ft_strcmp(node->key, key) == 0)
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

void	ht_remove_entry(t_ht *map, const char *key)
{
	size_t		index;
	t_ht_node	*prev;
	t_ht_node	*node;

	index = ht_hash(key, map->size);
	node = find_node(map, key, &prev, index);
	if (node)
		remove_node(map, node, prev, index);
}

void	ht_init_from_env(t_ht *map, char **envp)
{
	size_t	i;
	size_t	key_len;
	char	*equal;
	char	*key;
	char	*value;

	ht_init_map(map, 128);
	i = -1;
	while (envp[++i])
	{
		equal = ft_strchr(envp[i], '=');
		if (!equal)
			continue ;
		key_len = equal - envp[i];
		key = ft_substr(envp[i], 0, key_len);
		value = ft_substr(equal + 1, 0, ft_strlen(equal + 1));
		if (!ft_strcmp("SHLVL", key))
		{
			key_len = ft_atoi(value);
			free(value);
			value = ft_itoa(key_len + 1);
		}
		ht_set(map, key, value);
	}
}
