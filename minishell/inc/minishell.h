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

# include "enums.h"
# include "libft.h"
# include "get_next_line.h"
# include "readline.h"
# include "history.h"
# include "env.h"
# include "token_lst.h"
# include "ast.h"
# include "minishell_utils.h"
# include "builtins.h"

#endif
