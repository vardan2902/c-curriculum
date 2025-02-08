/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:46:11 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/02 16:23:20 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_node
{
	int				num;
	int				pos;
	int				move_count;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_dlst
{
	t_node	*head;
	size_t	size;
}	t_dlst;

typedef struct s_dstack
{
	t_dlst	*a;
	t_dlst	*b;
	char	*instructions;
}	t_dstack;

typedef struct s_int_tab
{
	int		*arr;
	size_t	size;
	size_t	min;
	size_t	max;
	size_t	mid;
}	t_int_tab;

typedef struct s_counter
{
	int	ra;
	int	rb;
	int	rra;
	int	rrb;
}	t_counter;

#endif
