/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:05:12 by ysaroyan          #+#    #+#             */
/*   Updated: 2025/03/24 20:05:14 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

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
void		update_or_add_node(t_ht *map, unsigned int index, const char *key,
				void *value);
void		add_new_node(t_ht *map, size_t index, const char *key, void *value);
size_t		ht_hash(const char *key, int size);
t_ht_node	*find_node(t_ht *map, const char *key, t_ht_node **prev,
				size_t index);
void		remove_node(t_ht *map, t_ht_node *node, t_ht_node *prev,
				size_t index);
char		***ht_to_entries(t_ht *map);
void		ht_clear(t_ht *map);

#endif
