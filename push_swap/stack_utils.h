/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:45:09 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/07 14:21:43 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_UTILS_H
# define STACK_UTILS_H

char		*count_best_moves(t_dstack *dstack);
void		push_to_b(t_dstack *dstack, t_int_tab tab);
void		sort3(t_dlst *stack);
void		init_and_check_tab(t_int_tab *tab);
t_node		*create_node(int n);
void		add_back(t_dlst *stack, t_node *new_node);
void		add_front(t_dlst *stack, t_node *new_node);
void		add(t_dlst *stack, int value);
void		init_stack(t_dlst *stack, t_int_tab *tab);
void		free_dstack(t_dstack *dstack);
t_dstack	*init_dstack(t_int_tab *tab);
size_t		get_matrix_len(char **matrix);
void		parse_args(int argc, char **argv, t_int_tab *tab);
int			is_tab_sorted(t_int_tab *tab);
int			contains_duplicates(t_int_tab *tab);
int			check_int_limit(const char *str);
void		sort_if_five(t_dstack *dstack);
void		push_first2_to_b(t_dstack *dstack);
void		final_order(t_dstack *dstack, int min);
t_node		*pop(t_dlst *stack);
void		swap(t_dlst *stack);
void		sa(t_dstack *dstack, char mode);
void		sb(t_dstack *dstack, char mode);
void		ss(t_dstack *dstack, char mode);
void		push(t_dlst *from_stack, t_dlst *to_stack);
void		pa(t_dstack *dstack, char mode);
void		pb(t_dstack *dstack, char mode);
void		rotate(t_dlst *stack);
void		ra(t_dstack *dstack, char mode);
void		rb(t_dstack *dstack, char mode);
void		rr(t_dstack *dstack, char mode);
void		rev_rotate(t_dlst *stack);
void		rra(t_dstack *dstack, char mode);
void		rrb(t_dstack *dstack, char mode);
void		rrr(t_dstack *dstack, char mode);
void		do_rule(t_dstack *dstack, char *str);
void		execute(t_dstack *dstack);
int			min(int a, int b);
int			max(int a, int b);
int			min_4(int a, int b, int c, int d);
void		put_error(void);
char		*get_min_instruction(t_dstack *dstack, t_node *node);
void		fill_counter_data(t_dstack *dstack, t_counter *counter,
				t_node *curr, int pos);
void		free_arg_matrix(char **matrix);
void		free_allocated(char **matrix, int *arr);

#endif
