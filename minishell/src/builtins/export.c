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
		if (node->key && ft_strchr("#?", node->key[0]))
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

void	print_env(t_ht *env)
{
	int		i;
	char	***env_entries;
	
	env_entries = ht_to_entries(env);
	i = -1;
	while (env_entries[++i])
	{
		printf("declare -x %s", env_entries[i][0]);
		if (env_entries[i][1])
			printf("=\"%s\"\n", env_entries[i][1]);
		else
			printf("\n");
	}
	free(env_entries);
}

int	is_valid_identifier(char *identifier)
{
	int	i;

	i = -1;
	while (identifier[++i])
	{
		if (i == 0 && (!ft_isalpha(identifier[i]) && identifier[i] != '_'))
			return (print_error("minishell: export: `", identifier, "': not a valid identifier"), 0);
		if (identifier[i] == '=')
			break ;
		if (!ft_isalnum(identifier[i]) && identifier[i] != '_')
			return (print_error("minishell: export: `", identifier, "': not a valid identifier"), 0);
	}
	return (1);
}

void	export_new_env(char *token, t_ht *env)
{
	char	*eq;

	eq = ft_strchr(token, '=');
	if (eq)
		ht_set(env, ft_substr(token, 0, eq - token), ft_substr(eq + 1, 0, ft_strlen(eq + 1)));
	else
		ht_set(env, ft_strdup(token), NULL);
}

int	ft_export(char **args, t_ht *env)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (args[i])
		++i;
	if (i == 1)
		return (print_env(env), 0);
	i = 0;
	while (args[++i])
	{
		if (is_valid_identifier(args[i]))
			export_new_env(args[i], env);
		else
			status = 1;
	}
	return (status);
}
