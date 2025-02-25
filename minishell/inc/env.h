#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_ht_node		t_ht_node;
typedef struct s_ht				t_ht;

struct s_ht_node
{
	char		*key;
	char		*value;
	t_ht_node	*next;
};

struct s_ht
{
	size_t		size;
	size_t		num_elements;
	t_ht_node	**table;
};

void		ht_init_from_env(t_ht *map, char **envp);
size_t		ht_hash(const char *key, int size);
void		ht_init_map(t_ht *map, size_t size);
void		ht_set(t_ht *map, const char *key, char *value);
char		*ht_get(t_ht *map, const char *key);
void		ht_remove_entry(t_ht *map, const char *key);
void		resize_map(t_ht *map);
t_ht_node	**create_new_table(size_t size);
void		rehash_nodes(t_ht *map, t_ht_node **new_table, size_t new_size);
char		**ht_to_matrix(t_ht *map);

#endif
