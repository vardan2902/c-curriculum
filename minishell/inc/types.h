/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:11:32 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/24 20:05:27 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_cmd			t_cmd;
typedef struct s_redirection	t_redirection;
typedef struct s_ast			t_ast;
typedef struct s_cmd_token		t_cmd_token;
typedef struct s_ht_node		t_ht_node;
typedef struct s_ht				t_ht;
typedef struct s_expand_ctx		t_expand_ctx;
typedef struct s_char_arr		t_char_arr;
typedef struct s_token			t_token;
typedef struct s_lst_with_it	t_lst_with_it;
typedef struct s_heredoc_ctx	t_heredoc_ctx;
typedef struct s_rm_quotes_ctx	t_rm_quotes_ctx;

struct s_char_arr
{
	char	**arr;
	size_t	size;
};

struct s_token
{
	char				*value;
	t_cmd_token_types	type;
};

struct s_lst_with_it
{
	t_list	**lst;
	t_list	**it;
};

struct s_redirection
{
	t_cmd_token_types	type;
	char				*target;
};

struct s_cmd
{
	char	*name;
	char	**args;
	t_list	*redirections;
};

struct s_ast
{
	t_cmd_token_types	token;
	t_cmd				*cmd;
	t_ast				*left;
	t_ast				*right;
	int					indent;
	bool				is_subshell;
};

struct s_cmd_token
{
	t_token				*token;
	t_list				*prev_token;
	t_cmd_token_types	type;
	ssize_t				size;
};

struct s_heredoc_ctx
{
	t_char_arr	target;
	bool		contain_quotes;
	char		*heredoc;
	int			fd;
};

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

struct s_expand_ctx
{
	char		**current;
	t_char_arr	*result;
	bool		in_double;
	bool		in_single;
	int			i;
};

struct s_rm_quotes_ctx
{
	size_t	len;
	size_t	i;
	size_t	j;
	size_t	new_len;
	bool	in_single_quotes;
	bool	in_double_quotes;
};

#endif
