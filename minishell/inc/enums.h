/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:12:21 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/24 15:12:36 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum e_cmd_token_types	t_cmd_token_types;
typedef enum e_quoting_state	t_quoting_state;

enum e_cmd_token_types
{
	T_NONE,
	T_WORD,
	T_CMD,
	T_PIPE,
	T_INPUT,
	T_OUTPUT,
	T_APPEND,
	T_HEREDOC,
	T_AND,
	T_OR,
	T_OPEN_PARENTHESIS,
	T_CLOSE_PARENTHESIS,
	T_UNHANDLED,
};

enum e_quoting_state
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE,
};

#endif
