/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:21:06 by vapetros          #+#    #+#             */
/*   Updated: 2025/02/07 13:24:52 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>

# include "libft.h"
# include "ft_printf.h"

# define RESET				"\033[0m"
# define BOLD_GREEN			"\033[1;32m"
# define BOLD_YELLOW		"\033[1;33m"
# define BOLD_CYAN			"\033[1;36m"
# define BOLD_RED			"\033[1;31m"
# define BOLD_WHITE			"\033[1;37m"

# define SLEEP_INTERRUPTED	1
# define RECEIVER			2
# define HANDSHAKE_DONE		4

typedef struct sigaction	t_sigaction;

#endif
