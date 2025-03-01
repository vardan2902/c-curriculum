#include "minishell.h"

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
		if (ft_strchr("#?", node->key[0]))
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
	size_t  i;
	size_t  j;
   
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

int	ft_export(char **args, t_ht *env)
{
	char	***env_entries;
	int		i;

	i = 0;
	while (args[i])
		++i;
	if (i == 1)
	{
		env_entries = ht_to_entries(env);
		i = -1;
		while (env_entries[++i])
		{
			printf("declare -x %s", env_entries[i][0]);
			if (env_entries[i][1][0])
				printf("=\"%s\"\n", env_entries[i][1]);
			else
				printf("\n");
			free(env_entries[i][0]);
			free(env_entries[i][1]);
		}
		free(env_entries);
	}
	return (0);
}
