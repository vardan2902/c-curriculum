/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaroyan <ysaroyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:15:47 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/24 20:05:47 by ysaroyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

char		*extract_var_name(const char *token, int *i);
t_char_arr	*expand_text(const char *token, t_ht *env);
void		expand_wildcards(t_char_arr *result);
void		remove_quotes(t_char_arr *result);
int			match_pattern(const char *pattern, const char *str);
char		*get_pattern(const char *token, int *ends_with_slash);
bool		should_show_hidden(const char *pattern);
void		handle_quotes(const char token, bool *in_single_quotes,
				bool *in_double_quotes);
t_char_arr	*init_expansion(char **current);
void		handle_regular_char(char token_char, char **current);
int			is_last_space(char *str);
void		init_expand_ctx(t_expand_ctx *ctx, t_char_arr *result,
				char **current);

#endif
