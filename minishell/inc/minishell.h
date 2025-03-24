/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:12:29 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/24 15:15:11 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READLINE_LIBRARY

# include <stdio.h>
# include <signal.h>
# include <curses.h>
# include <term.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/errno.h>

# include "libft.h"
# include "get_next_line_bonus.h"
# include "readline.h"
# include "history.h"
# include "enums.h"
# include "types.h"
# include "minishell_utils.h"
# include "env.h"
# include "token_lst.h"
# include "ast.h"
# include "builtins.h"
# include "expansion.h"

#endif
